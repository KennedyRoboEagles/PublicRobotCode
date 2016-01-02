#include "DriveLaterallyTimeCommand.h"

DriveLaterallyTimeCommand::DriveLaterallyTimeCommand(float time, float speed)
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(chassis);
	this->timer = new Timer();
	this->time = time;
	this->speed = speed;
}

// Called just before this Command runs the first time
void DriveLaterallyTimeCommand::Initialize()
{
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveLaterallyTimeCommand::Execute()
{
	chassis->FilteredCenter(this->speed);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveLaterallyTimeCommand::IsFinished()
{
	return this->timer->HasPeriodPassed(this->time);
}

// Called once after isFinished returns true
void DriveLaterallyTimeCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveLaterallyTimeCommand::Interrupted()
{

}
