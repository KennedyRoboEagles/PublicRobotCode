#include "SharonCommand.h"

SharonCommand::SharonCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void SharonCommand::Initialize()
{
	DriverStation::GetInstance()->ReportError("DO NOTHING!!!");
}

// Called repeatedly when this Command is scheduled to run
void SharonCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool SharonCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void SharonCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SharonCommand::Interrupted()
{

}
