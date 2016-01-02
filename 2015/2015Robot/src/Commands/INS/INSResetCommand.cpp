#include "INSResetCommand.h"
#include "INS/INS.h"

INSResetCommand::INSResetCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void INSResetCommand::Initialize()
{
	INS::GetInstance()->Reset();
}

// Called repeatedly when this Command is scheduled to run
void INSResetCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool INSResetCommand::IsFinished()
{
	return true;
}

// Called once after isFinished returns true
void INSResetCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void INSResetCommand::Interrupted()
{

}
