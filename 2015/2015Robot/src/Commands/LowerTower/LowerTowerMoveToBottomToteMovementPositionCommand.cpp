#include "LowerTowerMoveToBottomToteMovementPositionCommand.h"

LowerTowerMoveToBottomToteMovementPositionCommand::LowerTowerMoveToBottomToteMovementPositionCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToBottomToteMovementPositionCommand::Initialize()
{
	lowerTowerSubsystem->PositionBottomToteMovementPosition();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToBottomToteMovementPositionCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToBottomToteMovementPositionCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToBottomToteMovementPositionCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToBottomToteMovementPositionCommand::Interrupted()
{

}
