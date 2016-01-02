#include "INSEnableCommand.h"
#include "INS/INS.h"

INSEnableCommand::INSEnableCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void INSEnableCommand::Initialize()
{
	INS::GetInstance()->Enable();
}

// Called repeatedly when this Command is scheduled to run
void INSEnableCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool INSEnableCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void INSEnableCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void INSEnableCommand::Interrupted()
{

}
