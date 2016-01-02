#include "OpenIntakeCommand.h"

OpenIntakeCommand::OpenIntakeCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeGrabberSubsystem);
}

// Called just before this Command runs the first time
void OpenIntakeCommand::Initialize() {
	printf("[OpenIntakeCommand] Starting to open the grabber\n");
	intakeGrabberSubsystem->Open();
}

// Called repeatedly when this Command is scheduled to run
void OpenIntakeCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool OpenIntakeCommand::IsFinished() {
	return sensorSubsystem->GetIntakeOpenLimit();
}

// Called once after isFinished returns true
void OpenIntakeCommand::End() {
	printf("[OpenIntakeCommand] The grabber has reached the open limit\n");
	intakeGrabberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenIntakeCommand::Interrupted() {
	printf("[OpenIntakeCommand] Interrupted Stopping the grabber\n");
	intakeGrabberSubsystem->Stop();
}
