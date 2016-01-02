#include "TestIntakeOpenCommand.h"

TestIntakeOpenCommand::TestIntakeOpenCommand() : CommandBase("TestIntakeOpenCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeGrabberSubsystem);
}

// Called just before this Command runs the first time
void TestIntakeOpenCommand::Initialize() {
	intakeGrabberSubsystem->Open();
}

// Called repeatedly when this Command is scheduled to run
void TestIntakeOpenCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestIntakeOpenCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestIntakeOpenCommand::End() {
	intakeGrabberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestIntakeOpenCommand::Interrupted() {
	intakeGrabberSubsystem->Stop();
}
