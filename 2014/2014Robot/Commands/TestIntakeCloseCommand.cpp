#include "TestIntakeCloseCommand.h"

TestIntakeCloseCommand::TestIntakeCloseCommand() : CommandBase("TestIntakeCloseCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeGrabberSubsystem);
}

// Called just before this Command runs the first time
void TestIntakeCloseCommand::Initialize() {
	intakeGrabberSubsystem->Close();
}

// Called repeatedly when this Command is scheduled to run
void TestIntakeCloseCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestIntakeCloseCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestIntakeCloseCommand::End() {
	intakeGrabberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestIntakeCloseCommand::Interrupted() {
	intakeGrabberSubsystem->Stop();
}
