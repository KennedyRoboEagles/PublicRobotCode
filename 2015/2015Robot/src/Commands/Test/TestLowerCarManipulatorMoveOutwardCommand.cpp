#include "TestLowerCarManipulatorMoveOutwardCommand.h"

TestLowerCarManipulatorMoveOutwardCommand::TestLowerCarManipulatorMoveOutwardCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerCarManipulatorSubsystem);
}

// Called just before this Command runs the first time
void TestLowerCarManipulatorMoveOutwardCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void TestLowerCarManipulatorMoveOutwardCommand::Execute()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.4);
}

// Make this return true when this Command no longer needs to run execute()
bool TestLowerCarManipulatorMoveOutwardCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestLowerCarManipulatorMoveOutwardCommand::End()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestLowerCarManipulatorMoveOutwardCommand::Interrupted()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);
}
