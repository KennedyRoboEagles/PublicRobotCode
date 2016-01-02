#include "LowerTowerLowerToteCommand.h"

LowerTowerLowerToteCommand::LowerTowerLowerToteCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerLowerToteCommand::Initialize()
{
	lowerTowerSubsystem->PositionLowerTote();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerLowerToteCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerLowerToteCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerLowerToteCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerLowerToteCommand::Interrupted()
{

}
