#include "TestLowerTowerMoveUpCommand.h"

TestLowerTowerMoveUpCommand::TestLowerTowerMoveUpCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerTowerSubsystem);
}

// Called just before this Command runs the first time
void TestLowerTowerMoveUpCommand::Initialize()
{
	lowerTowerSubsystem->DogGearBackward();
}

// Called repeatedly when this Command is scheduled to run
void TestLowerTowerMoveUpCommand::Execute()
{
	lowerTowerSubsystem->DogGearRun();
}

// Make this return true when this Command no longer needs to run execute()
bool TestLowerTowerMoveUpCommand::IsFinished()
{
	return lowerTowerSubsystem->GetTopLimit();
}

// Called once after isFinished returns true
void TestLowerTowerMoveUpCommand::End()
{
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestLowerTowerMoveUpCommand::Interrupted()
{
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
}
