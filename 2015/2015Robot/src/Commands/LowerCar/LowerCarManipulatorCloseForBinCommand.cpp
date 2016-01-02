#include "LowerCarManipulatorCloseForBinCommand.h"

LowerCarManipulatorCloseForBinCommand::LowerCarManipulatorCloseForBinCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerCarManipulatorCloseForBinCommand::Initialize()
{
	lowerCarManipulatorSubsystem->ResetToteState();
	lowerCarManipulatorSubsystem->SetCurrentState(LowerCarManipulatorSubsystem::MS_CloseForBin);
}

// Called repeatedly when this Command is scheduled to run
void LowerCarManipulatorCloseForBinCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerCarManipulatorCloseForBinCommand::IsFinished()
{
	return lowerCarManipulatorSubsystem->IsDone();
}

// Called once after isFinished returns true
void LowerCarManipulatorCloseForBinCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerCarManipulatorCloseForBinCommand::Interrupted()
{

}
