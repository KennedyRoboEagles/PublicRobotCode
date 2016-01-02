#include "LowerTowerMoveToBottomCommand.h"

LowerTowerMoveToBottomCommand::LowerTowerMoveToBottomCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToBottomCommand::Initialize()
{
	lowerTowerSubsystem->PositionBottom();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToBottomCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToBottomCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToBottomCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToBottomCommand::Interrupted()
{

}
