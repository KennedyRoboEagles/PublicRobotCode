#include "LowerTowerMoveToPickupBinPositionCommand.h"

LowerTowerMoveToPickupBinPositionCommand::LowerTowerMoveToPickupBinPositionCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToPickupBinPositionCommand::Initialize()
{
	lowerTowerSubsystem->PositionPickedUpBin();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToPickupBinPositionCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToPickupBinPositionCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToPickupBinPositionCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToPickupBinPositionCommand::Interrupted()
{

}
