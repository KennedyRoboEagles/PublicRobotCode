#include "TestThrowCommand.h"

TestThrowCommand::TestThrowCommand() : CommandBase("TestThrowCommand") {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
}

// Called just before this Command runs the first time
void TestThrowCommand::Initialize() {
	throwerSubsystem->SetInSolenoids(false);
	throwerSubsystem->SetOutSolenois(true);
}

// Called repeatedly when this Command is scheduled to run
void TestThrowCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TestThrowCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TestThrowCommand::End() {
	throwerSubsystem->SetInSolenoids(false);
	throwerSubsystem->SetOutSolenois(false);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TestThrowCommand::Interrupted() {
	throwerSubsystem->SetInSolenoids(false);
	throwerSubsystem->SetOutSolenois(false);
}
