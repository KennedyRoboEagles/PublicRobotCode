#include <Commands/LowerCar/LowerCarManipulatorSupervisorCommand.h>
#include <Subsystems/LowerCarManipulatorSubsystem.h>
#include "../RobotMap.h"

const float RELEASE_DISTANCE = 3;

const float ACQUIRED_TOTE_CURRENT = 28;
const float MAX_ALLOWABLE_CURRENT = 10;

const float MAX_OPEN_DISTANCE = 28.5;

/*
 * This subsystem assumes that the Jaguar controlling the manipulator motor is wired with limit
 * switches to set the outer limits.  It uses the current values from the PDP to detect when
 * the inner and outer limits have been breached.
 *
 * Potential improvements:
 *
 * Use a PID to control the sizing, rather than directly controlling
 * the motors.
 *
 * Do a better job of detecting stalled motors
 */
LowerCarManipulatorSubsystem::LowerCarManipulatorSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("LowerCarManipulatorSubsystem") {

	this->sensorSubsystem = sensorSubsystem;
	this->subsystemState = LowerCarManipulatorSubsystem::MS_Unknown;
	this->calibrationState = LowerCarManipulatorSubsystem::Uncalibrated;
	this->toteState = LowerCarManipulatorSubsystem::NoTote;
	this->isDone = false;
	this->manipulatorMotor = new CANJaguar(LCAR_MANIPULATOR_JAGUAR);
	this->manipulatorMotor->SetPercentMode();
	this->manipulatorMotor->EnableControl();
	this->manipulatorMotor->Set(0.0);

	this->currentFilter = DaisyFilter::MovingAverageFilter(5);
	this->filteredCurrent = 0.0;

	this->maxPosition = MAX_OPEN_DISTANCE;

	this->sd = new GrabberSD();
	SmartDashboard::PutData(this->sd);
	this->sd->UpdateCurrentDraw(0.0);
	this->sd->UpdateCurrentPosition(0.0);
	this->sd->UpdateDelta(0.0);
	this->sd->UpdateIsDone(false);
	this->sd->UpdatePosition("Default Position");
	this->sd->UpdateSetpoint(0.0);
	this->sd->UpdateState("Default State");
}

void LowerCarManipulatorSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new LowerCarManipulatorSupervisorCommand());
}

LowerCarManipulatorSubsystem::LowerCarManipulatorState LowerCarManipulatorSubsystem::GetCurrentState()
{
	return this->subsystemState;
}

void LowerCarManipulatorSubsystem::SetCurrentState(LowerCarManipulatorState newState)
{
	// TODO validate whether we can transition to new state now
	this->subsystemState = newState;
}

void LowerCarManipulatorSubsystem::Calibrate()
{
	this->UpdateCurrent();
	switch(this->calibrationState)
	{
	case Uncalibrated:
		this->calibrationState = StartClosing;
		break;
	case StartClosing:
		printf("Calibration: StartClosing\n");
		this->manipulatorMotor->Set(closingSpeed);
		this->zeroCurrentSampleCount = 0;
		this->calibrationState = Closing;
		break;

	case Closing:
		printf("Calibration: Closing.  Current is %f\n", this->GetManipulatorMotorCurrent());
		this->manipulatorMotor->Set(closingSpeed);
		//if (this->GetManipulatorMotorCurrent() == 0)
		//{
		//	this->zeroCurrentSampleCount++;
		//}
		//else
		//{
		//	this->zeroCurrentSampleCount = 0;
		//}

		//if (this->zeroCurrentSampleCount > 3)
		if(this->GetManipulatorForwardLimit())
		{
			this->sensorSubsystem->GetLowerCarManipulatorEncoder()->Reset();
			this->calibrationState = Calibrated;
		}
		break;

	case Calibrated:
		printf("Calibrated.  %f maximum opening size detected. \n", this->maxPosition);
		this->toteState = NoTote;
		break;
	}
}

void LowerCarManipulatorSubsystem::AcquireTote()
{
	this->UpdateCurrent();
	switch (this->toteState)
	{
	case NoTote:
		printf("Acquire: noTote\n");
		this->toteState = AcquiringTote;
		this->heldPosition = 0;
		this->isDone = false;
		break;
	case AcquiringTote:
		printf("Acquire: AquiringTote.  Current %f, position %f\n",
				this->GetManipulatorMotorCurrent(), this->GetManipulatorPosition());
		this->isDone = false;
		// TODO tune value below.  Also consider taking slope of samples here rather than
		// just a max value.
		if (this->filteredCurrent > ACQUIRED_TOTE_CURRENT)
		{
			this->toteState = HaveTote;
			this->manipulatorMotor->Set(0);
		}
		else if (this->GetManipulatorPosition() <= 0 || this->GetManipulatorForwardLimit())
		{
			this->manipulatorMotor->Set(0);
			this->toteState = NoToteFound;
		}
		else
		{
			this->manipulatorMotor->Set(closingSpeed);
		}
		break;
	case HaveTote:
		printf("Have Tote\n");
		this->heldPosition = this->GetManipulatorPosition();
		this->isDone = true;
		break;
	case NoToteFound:
		printf("No Tote Found\n");
		this->isDone = true;
		break;
	}

	this->sd->UpdateSetpoint(0.0);
}

void LowerCarManipulatorSubsystem::ReleaseTote()
{
	this->UpdateCurrent();
	// Opens it one inch from the position we recorded when we held it
	if (this->GetManipulatorPosition() < this->heldPosition + RELEASE_DISTANCE)
	{
		this->manipulatorMotor->Set(openingSpeed);
		this->isDone = false;
	}
	else
	{
		this->manipulatorMotor->Set(0);
		this->isDone = true;
	}
}

void LowerCarManipulatorSubsystem::SetSize(double sizeInInches)
{
	this->UpdateCurrent();
	// TODO this could be improved to use a PID to be more precise
	double delta = this->GetManipulatorPosition() - sizeInInches;
	printf("Size %f, Delta %f\n", sizeInInches, delta);
	if (delta > 0.1)
	{
		this->manipulatorMotor->Set(closingSpeed);
		this->isDone = false;
	}
	else if (delta < -0.1)
	{
		this->manipulatorMotor->Set(openingSpeed);
		this->isDone = false;
	}
	else
	{
		this->manipulatorMotor->Set(0);
		this->isDone = true;
	}

	if(this->GetManipulatorForwardLimit() || this->GetManipulatorReverseLimit()) {
		this->isDone = true;
	}

	this->sd->UpdateSetpoint(sizeInInches);
	this->sd->UpdateDelta(delta);
}

double LowerCarManipulatorSubsystem::GetManipulatorMotorCurrent()
{
	return this->manipulatorMotor->GetOutputCurrent();
}

double LowerCarManipulatorSubsystem::GetManipulatorPosition()
{
	return this->sensorSubsystem->GetLowerCarOpenDistance();
}

CANJaguar *LowerCarManipulatorSubsystem::GetManipulatorMotor() {
	return this->manipulatorMotor;
}

LowerCarManipulatorSubsystem::ToteState LowerCarManipulatorSubsystem::GetToteState() {
	return this->toteState;
}

bool LowerCarManipulatorSubsystem::IsDone() {
	return this->isDone;
}

bool LowerCarManipulatorSubsystem::GetManipulatorForwardLimit() {
	return !this->manipulatorMotor->GetForwardLimitOK();
}

bool LowerCarManipulatorSubsystem::GetManipulatorReverseLimit() {
	return !this->manipulatorMotor->GetReverseLimitOK();
}

void LowerCarManipulatorSubsystem::UpdateCurrent() {
	this->filteredCurrent = this->currentFilter->Calculate(this->GetManipulatorMotorCurrent());
}

bool LowerCarManipulatorSubsystem::IsCurrentOk() {
	return MAX_ALLOWABLE_CURRENT <= this->filteredCurrent;
}

void LowerCarManipulatorSubsystem::ResetToteState() {
	this->toteState = NoTote;
}


void LowerCarManipulatorSubsystem::ResetIsDone() {
	this->isDone = false;
}

GrabberSD *LowerCarManipulatorSubsystem::GetSD() {
	return this->sd;
}
