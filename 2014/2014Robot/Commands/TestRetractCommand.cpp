#include "TestRetractCommand.h"

TestRetractCommand::TestRetractCommand() : CommandBase("TestRetractCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
}

// Called just before this Command runs the first time
void TestRetractCommand::Initialize() {
	throwerSubsystem->SetInSolenoids(true);
	throwerSubsystem->SetOutSolenois(false);
}

// Called repeatedly when this Command is scheduled to run
void TestRetractCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestRetractCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestRetractCommand::End() {
	throwerSubsystem->SetInSolenoids(false);
	throwerSubsystem->SetOutSolenois(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestRetractCommand::Interrupted() {
	throwerSubsystem->SetInSolenoids(false);
	throwerSubsystem->SetOutSolenois(false);
}
