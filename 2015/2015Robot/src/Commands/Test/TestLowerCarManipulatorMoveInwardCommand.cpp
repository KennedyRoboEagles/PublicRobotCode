#include "TestLowerCarManipulatorMoveInwardCommand.h"

TestLowerCarManipulatorMoveInwardCommand::TestLowerCarManipulatorMoveInwardCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(lowerCarManipulatorSubsystem);
}

// Called just before this Command runs the first time
void TestLowerCarManipulatorMoveInwardCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TestLowerCarManipulatorMoveInwardCommand::Execute() {
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(-0.4);
}

// Make this return true when this Command no longer needs to run execute()
bool TestLowerCarManipulatorMoveInwardCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void TestLowerCarManipulatorMoveInwardCommand::End()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestLowerCarManipulatorMoveInwardCommand::Interrupted()
{
	lowerCarManipulatorSubsystem->GetManipulatorMotor()->Set(0.0);
}
