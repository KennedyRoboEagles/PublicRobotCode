#include "LowerTowerMoveToStackUpCommand.h"

LowerTowerMoveToStackUpCommand::LowerTowerMoveToStackUpCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerMoveToStackUpCommand::Initialize()
{
	lowerTowerSubsystem->PositionStackTote();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerMoveToStackUpCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerMoveToStackUpCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerMoveToStackUpCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerMoveToStackUpCommand::Interrupted()
{

}
