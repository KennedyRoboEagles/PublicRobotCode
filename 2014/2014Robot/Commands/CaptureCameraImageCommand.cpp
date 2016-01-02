#include "CaptureCameraImageCommand.h"

CaptureCameraImageCommand::CaptureCameraImageCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(visionSubsystem);
}

// Called just before this Command runs the first time
void CaptureCameraImageCommand::Initialize() {
	printf("[CaptureCameraImage] Capturing a image from the axis camera\n");
	visionSubsystem->WriteCameraImage();
	
}

// Called repeatedly when this Command is scheduled to run
void CaptureCameraImageCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool CaptureCameraImageCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void CaptureCameraImageCommand::End() {
	
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CaptureCameraImageCommand::Interrupted() {
}
