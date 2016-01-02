#include "TestIntakeTiltUpCommand.h"

#define INTAKE_UPSPEED 0.25

TestIntakeTiltUpCommand::TestIntakeTiltUpCommand() : CommandBase("TestIntakeTiltUpCommand") {
	Requires(intakeTiltSubsystem);
}

// Called just before this Command runs the first time
void TestIntakeTiltUpCommand::Initialize() {
	intakeTiltSubsystem->TiltUp();
}

// Called repeatedly when this Command is scheduled to run
void TestIntakeTiltUpCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestIntakeTiltUpCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestIntakeTiltUpCommand::End() {
	intakeTiltSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestIntakeTiltUpCommand::Interrupted() {
	intakeTiltSubsystem->Stop();
}
