#include "LowerCarManipulatorOpenForNarrowToteCommand.h"

LowerCarManipulatorOpenForNarrowToteCommand::LowerCarManipulatorOpenForNarrowToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorOpenForNarrowToteCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetToteState();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_OpenForNarrowTote);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorOpenForNarrowToteCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorOpenForNarrowToteCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorOpenForNarrowToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorOpenForNarrowToteCommand::Interrupted()
{

}
