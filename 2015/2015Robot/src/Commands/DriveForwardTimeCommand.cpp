#include "DriveForwardTimeCommand.h"

DriveForwardTimeCommand::DriveForwardTimeCommand(float time, float speed)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(chassis);
	this->timer = new Timer();
	this->time = time;
	this->speed = speed;
}

// Called just before this Command runs the first time
void DriveForwardTimeCommand::Initialize()
{
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardTimeCommand::Execute()
{
	chassis->GetDrive()->ArcadeDrive(this->speed, 0.0, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardTimeCommand::IsFinished()
{
	return this->timer->HasPeriodPassed(this->time);
}

// Called once after isFinished returns true
void DriveForwardTimeCommand::End()
{
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardTimeCommand::Interrupted()
{
	chassis->Stop();
}
