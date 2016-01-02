#include "LowerTowerMoveToPickUpPositionCommand.h"

LowerTowerMoveToPickUpPositionCommand::LowerTowerMoveToPickUpPositionCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToPickUpPositionCommand::Initialize()
{
	lowerTowerSubsystem->PositionPickUpTote();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToPickUpPositionCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToPickUpPositionCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToPickUpPositionCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToPickUpPositionCommand::Interrupted()
{

}
