#include "INSDisableCommand.h"
#include "INS/INS.h"

INSDisableCommand::INSDisableCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void INSDisableCommand::Initialize()
{
	INS::GetInstance()->Disable();
}

// Called repeatedly when this Command is scheduled to run
void INSDisableCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool INSDisableCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void INSDisableCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void INSDisableCommand::Interrupted()
{

}
