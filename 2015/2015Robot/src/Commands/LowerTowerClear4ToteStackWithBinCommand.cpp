#include "LowerTowerClear4ToteStackWithBinCommand.h"

LowerTowerClear4ToteStackWithBinCommand::LowerTowerClear4ToteStackWithBinCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
}

// Called just before this Command runs the first time
void LowerTowerClear4ToteStackWithBinCommand::Initialize()
{
	lowerTowerSubsystem->PositionBinClear4Stack();
}

// Called repeatedly when this Command is scheduled to run
void LowerTowerClear4ToteStackWithBinCommand::Execute()
{

}

// Make this return true when this Command no longer needs to run execute()
bool LowerTowerClear4ToteStackWithBinCommand::IsFinished()
{
	return lowerTowerSubsystem->IsAtPosition();
}

// Called once after isFinished returns true
void LowerTowerClear4ToteStackWithBinCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void LowerTowerClear4ToteStackWithBinCommand::Interrupted()
{

}
