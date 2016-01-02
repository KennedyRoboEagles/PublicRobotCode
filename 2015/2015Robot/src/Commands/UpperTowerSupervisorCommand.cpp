#include "UpperTowerSupervisorCommand.h"

const float P_GAIN = 0;
const float I_GAIN = 0;
const float D_GAIN = 0;
const float FEEED_FORWARD = 0;

const float INPUT_RANGE_MIN = 0;
const float INPUT_RANGE_MAX = 0;
const float OUTPUT_RANGE_MIN = -1.0;
const float OUTPUT_RANGE_MAX = 1.0;

const float ABSOLUTE_TOLLERANCE = 100;
const float CALIBRATION_TIMEOUT = 5;

const int SETPOINT_TOP = 0;
const int SETPOINT_PICKUP = 0;
const int SETPOINT_STACK = 0;


UpperTowerSupervisorCommand::UpperTowerSupervisorCommand() {
	Requires(upperTowerSubsystem);
	this->controller = new PIDController(P_GAIN, I_GAIN, D_GAIN,FEEED_FORWARD, upperTowerSubsystem->GetEncoder(), upperTowerSubsystem->GetVerticalJaguar());
	this->controller->SetInputRange(INPUT_RANGE_MIN, INPUT_RANGE_MAX);
	this->controller->SetOutputRange(OUTPUT_RANGE_MIN, OUTPUT_RANGE_MAX);
	this->controller->Reset();
	this->controller->Disable();

	this->timer = new Timer();

	this->isCalibrated = false;
	this->paused = false;
	this->pausedSetpoint = 0;
	this->setpoint = 0;
}

// Called just before this Command runs the first time
void UpperTowerSupervisorCommand::Initialize()
{
	upperTowerSubsystem->StopMotor();
	if(!this->isCalibrated) {
		upperTowerSubsystem->SetState(UpperTowerSubsystem::EnterCalibration);
	} else {
		upperTowerSubsystem->SetState(UpperTowerSubsystem::Running);
	}
	this->controller->Reset();
	this->controller->Disable();
	this->timer->Reset();
}

// Called repeatedly when this Command is scheduled to run
void UpperTowerSupervisorCommand::Execute()
{
	switch(upperTowerSubsystem->GetState()) {
	case UpperTowerSubsystem::EnterCalibration:
		this->controller->Disable();
		if(upperTowerSubsystem->GetTopLimit()) {
			upperTowerSubsystem->SetState(UpperTowerSubsystem::CalibrationReached);
			break;
		}
		this->timer->Reset();
		this->timer->Start();
		upperTowerSubsystem->SetState(UpperTowerSubsystem::Calibration);
		break;
	case UpperTowerSubsystem::Calibration:
		if(upperTowerSubsystem->GetTopLimit()) {
			upperTowerSubsystem->SetState(UpperTowerSubsystem::CalibrationReached);
			break;
		}
		if(CALIBRATION_TIMEOUT < this->timer->Get()) {
			upperTowerSubsystem->SetState(UpperTowerSubsystem::Stopped);
			this->isCalibrated = false;
			break;
		}

		upperTowerSubsystem->MoveUp();
		break;

	case UpperTowerSubsystem::CalibrationReached:
		upperTowerSubsystem->StopMotor();
		upperTowerSubsystem->ResetEncoder();
		this->isCalibrated = true;
		upperTowerSubsystem->SetState(UpperTowerSubsystem::Running);
		this->controller->Disable();
		break;
	case UpperTowerSubsystem::Running:
		if(upperTowerSubsystem->GetTopLimit()) {
		this->controller->Disable();
		} else {
			this->run();
		}
		break;
	case UpperTowerSubsystem::Stopped:
		this->controller->Disable();
		break;
	default:
		this->controller->Disable();
	}
}

// Make this return true when this Command no longer needs to run execute()
bool UpperTowerSupervisorCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void UpperTowerSupervisorCommand::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void UpperTowerSupervisorCommand::Interrupted() {
	this->cleanUp();
}

void UpperTowerSupervisorCommand::run() {
	switch(upperTowerSubsystem->GetPosition()) {
	case UpperTowerSubsystem::TopPosition:
		this->paused  = false;
		this->setpoint = SETPOINT_TOP;
		break;
	case UpperTowerSubsystem::StackPosition:
		this->paused  = false;
		this->setpoint = SETPOINT_STACK;
		break;
	case UpperTowerSubsystem::PickUpPosition:
		this->paused  = false;
		this->setpoint = SETPOINT_PICKUP;
		break;
	case UpperTowerSubsystem::StoppedAtCurrentPosition:
		if(this->paused) {
			this->setpoint = this->pausedSetpoint;
		} else {
			this->paused  = true;
			this->pausedSetpoint = upperTowerSubsystem->GetEncoderCount();
		}
		break;
	default:
		this->paused  = false;
	}

	this->controller->Enable();
	this->controller->SetSetpoint(this->setpoint);
}

void UpperTowerSupervisorCommand::cleanUp() {
	this->timer->Reset();
	this->controller->Reset();
	this->controller->Disable();
	upperTowerSubsystem->StopMotor();
	this->paused = false;
}
