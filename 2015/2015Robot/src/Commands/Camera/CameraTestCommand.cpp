#include "CameraTestCommand.h"

CameraTestCommand::CameraTestCommand()
{
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(chassis);
	Requires(cameraSubsystem);
}

// Called just before this Command runs the first time
void CameraTestCommand::Initialize()
{
	SmartDashboard::PutNumber("Camera Angle", 1);
	SmartDashboard::PutBoolean("Camera Led", false);
}

// Called repeatedly when this Command is scheduled to run
void CameraTestCommand::Execute()
{
	float angle = SmartDashboard::GetNumber("Camera Angle", 1);
	bool led = SmartDashboard::GetBoolean("Camera Led", false);
	cameraSubsystem->SetLedRingState(led);
	cameraSubsystem->SetCameraTiltRawServo(angle);
}

// Make this return true when this Command no longer needs to run execute()
bool CameraTestCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CameraTestCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraTestCommand::Interrupted()
{

}
