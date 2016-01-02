#include "TestUpperTowerMoveUpCommand.h"

TestUpperTowerMoveUpCommand::TestUpperTowerMoveUpCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(upperTowerSubsystem);
}

// Called just before this Command runs the first time
void TestUpperTowerMoveUpCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TestUpperTowerMoveUpCommand::Execute()
{
	upperTowerSubsystem->MoveDown();
}

// Make this return true when this Command no longer needs to run execute()
bool TestUpperTowerMoveUpCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestUpperTowerMoveUpCommand::End()
{
	upperTowerSubsystem->StopMotor();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestUpperTowerMoveUpCommand::Interrupted()
{
	upperTowerSubsystem->StopMotor();
}
