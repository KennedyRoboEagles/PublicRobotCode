#include "LowerCarManipulatorAcquireToteCommand.h"

LowerCarManipulatorAcquireToteCommand::LowerCarManipulatorAcquireToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorAcquireToteCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetToteState();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_AcquireTote);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorAcquireToteCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorAcquireToteCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorAcquireToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorAcquireToteCommand::Interrupted()
{

}
