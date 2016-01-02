#include "TestLowerTowerMoveDownCommand.h"

TestLowerTowerMoveDownCommand::TestLowerTowerMoveDownCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerTowerSubsystem);
}

// Called just before this Command runs the first time
void TestLowerTowerMoveDownCommand::Initialize()
{
	lowerTowerSubsystem->DogGearForward();
}

// Called repeatedly when this Command is scheduled to run
void TestLowerTowerMoveDownCommand::Execute()
{
	lowerTowerSubsystem->DogGearRun();
}

// Make this return true when this Command no longer needs to run execute()
bool TestLowerTowerMoveDownCommand::IsFinished()
{
	return towerSubsystem->GetBottomLimit();
}

// Called once after isFinished returns true
void TestLowerTowerMoveDownCommand::End()
{
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestLowerTowerMoveDownCommand::Interrupted()
{
	lowerTowerSubsystem->DogGearStop();
	lowerTowerSubsystem->DogGearRun();
}
