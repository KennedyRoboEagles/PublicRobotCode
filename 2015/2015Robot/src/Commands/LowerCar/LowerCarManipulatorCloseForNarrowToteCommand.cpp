#include "LowerCarManipulatorCloseForNarrowToteCommand.h"

LowerCarManipulatorCloseForNarrowToteCommand::LowerCarManipulatorCloseForNarrowToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorCloseForNarrowToteCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetToteState();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_CloseForNarrowTote);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorCloseForNarrowToteCommand::Execute()
{
	printf("Waiting for grabber\n");
}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorCloseForNarrowToteCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorCloseForNarrowToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorCloseForNarrowToteCommand::Interrupted()
{

}
