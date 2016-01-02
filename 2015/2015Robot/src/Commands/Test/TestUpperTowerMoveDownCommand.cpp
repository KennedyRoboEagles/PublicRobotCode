#include "TestUpperTowerMoveDownCommand.h"

TestUpperTowerMoveDownCommand::TestUpperTowerMoveDownCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(upperTowerSubsystem);
}

// Called just before this Command runs the first time
void TestUpperTowerMoveDownCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TestUpperTowerMoveDownCommand::Execute()
{
	upperTowerSubsystem->MoveUp();
}

// Make this return true when this Command no longer needs to run execute()
bool TestUpperTowerMoveDownCommand::IsFinished()
{
	return towerSubsystem->GetBottomLimit();
}

// Called once after isFinished returns true
void TestUpperTowerMoveDownCommand::End()
{
	upperTowerSubsystem->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestUpperTowerMoveDownCommand::Interrupted()
{
	upperTowerSubsystem->StopMotor();
}
