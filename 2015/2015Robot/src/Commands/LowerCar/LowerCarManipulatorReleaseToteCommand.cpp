#include "LowerCarManipulatorReleaseToteCommand.h"

LowerCarManipulatorReleaseToteCommand::LowerCarManipulatorReleaseToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorReleaseToteCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetToteState();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_ReleaseTote);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorReleaseToteCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorReleaseToteCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorReleaseToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorReleaseToteCommand::Interrupted()
{

}
