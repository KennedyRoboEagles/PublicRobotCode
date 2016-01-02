#include "LowerCarManipulatorDeathCommand.h"

const double TIME = 10;

LowerCarManipulatorDeathCommand::LowerCarManipulatorDeathCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerCarManipulatorSubsystem);
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void LowerCarManipulatorDeathCommand::Initialize() {
	this->timer->Stop();
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);
	this->oppening = true;
	this->encoderCal = false;
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorDeathCommand::Execute() {
	if(!encoderCal && !lowerCarManipulatorSubsystem->GetManipulatorMotor()->GetForwardLimitOK()) {
		sensorSubsystem->GetLowerCarManipulatorEncoder()->Reset();
		this->encoderCal = true;
	}

	if(oppening) {
		lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(1.0);
	} else {
		lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(-1.0);
	}

	if(this->timer->Get() > TIME) {
		this->timer->Stop();
		this->timer->Reset();
		this->timer->Start();
		this->oppening = !this->oppening;
	}

	SmartDashboard::PutBoolean("Opening", this->oppening);
	SmartDashboard::PutBoolean("Forward Limit", lowerCarManipulatorSubsystem->GetManipulatorMotor()->GetForwardLimitOK());
	SmartDashboard::PutBoolean("Backward Limit", lowerCarManipulatorSubsystem->GetManipulatorMotor()->GetReverseLimitOK());
	SmartDashboard::PutNumber("Current JAG", lowerCarManipulatorSubsystem->GetManipulatorMotor()->GetOutputCurrent());
	SmartDashboard::PutBoolean("Encoder Caled", this->encoderCal);
}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorDeathCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void LowerCarManipulatorDeathCommand::End()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorDeathCommand::Interrupted()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);

}
