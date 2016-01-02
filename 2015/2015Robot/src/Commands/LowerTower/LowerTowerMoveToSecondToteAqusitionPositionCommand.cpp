#include "LowerTowerMoveToSecondToteAqusitionPositionCommand.h"

LowerTowerMoveToSecondToteAqusitionPositionCommand::LowerTowerMoveToSecondToteAqusitionPositionCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToSecondToteAqusitionPositionCommand::Initialize()
{
	lowerTowerSubsystem->PositionSecondToteAcquisition();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToSecondToteAqusitionPositionCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToSecondToteAqusitionPositionCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToSecondToteAqusitionPositionCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToSecondToteAqusitionPositionCommand::Interrupted()
{

}
