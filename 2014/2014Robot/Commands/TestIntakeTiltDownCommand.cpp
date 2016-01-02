#include "TestIntakeTiltDownCommand.h"

TestIntakeTiltDownCommand::TestIntakeTiltDownCommand() : CommandBase("TestIntakeTiltDownCommand") {
	Requires(intakeTiltSubsystem);
}

// Called just before this Command runs the first time
void TestIntakeTiltDownCommand::Initialize() {
	intakeTiltSubsystem->TiltDown();
}

// Called repeatedly when this Command is scheduled to run
void TestIntakeTiltDownCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool TestIntakeTiltDownCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestIntakeTiltDownCommand::End() {
	intakeTiltSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestIntakeTiltDownCommand::Interrupted() {
	intakeTiltSubsystem->Stop();
}
