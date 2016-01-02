#include "LowerCarManipulatorOpenForWideToteCommand.h"

LowerCarManipulatorOpenForWideToteCommand::LowerCarManipulatorOpenForWideToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorOpenForWideToteCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetIsDone();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_OpenForWideTote);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorOpenForWideToteCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorOpenForWideToteCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorOpenForWideToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorOpenForWideToteCommand::Interrupted()
{

}
