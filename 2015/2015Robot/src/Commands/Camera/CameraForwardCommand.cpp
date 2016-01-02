#include "CameraForwardCommand.h"

/*
 * Points the camera straight forward.
 */
CameraForwardCommand::CameraForwardCommand()
{
	Requires(cameraSubsystem);
}

// Called just before this Command runs the first time
void CameraForwardCommand::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void CameraForwardCommand::Execute()
{
	// Value determined experimentally
	cameraSubsystem->SetCameraTiltRawServo(.65);
}

// Make this return true when this Command no longer needs to run execute()
bool CameraForwardCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void CameraForwardCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CameraForwardCommand::Interrupted()
{

}
