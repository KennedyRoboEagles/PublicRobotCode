#include "CloseIntakeCommand.h"

CloseIntakeCommand::CloseIntakeCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeGrabberSubsystem);
}

// Called just before this Command runs the first time
void CloseIntakeCommand::Initialize() {
	printf("[CloseIntakeCommand] Starting to close intake\n");
	intakeGrabberSubsystem->Close();
}

// Called repeatedly when this Command is scheduled to run
void CloseIntakeCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool CloseIntakeCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void CloseIntakeCommand::End() {
	printf("[CloseIntakeCommand] This command ended some how?\n");
	intakeGrabberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CloseIntakeCommand::Interrupted() {
	printf("[CloseIntakeCommand] Interrupted Stopping the grabber\n");
	intakeGrabberSubsystem->Stop();
}
