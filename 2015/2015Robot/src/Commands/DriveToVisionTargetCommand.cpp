#include "DriveToVisionTargetCommand.h"
#include <cmath>

/*
 * This command acquires the vision target, and drives the robot to it
 */
DriveToVisionTargetCommand::DriveToVisionTargetCommand()
{
	Requires(chassis);
	Requires(cameraSubsystem);
}

// Called just before this Command runs the first time
void DriveToVisionTargetCommand::Initialize()
{
	this->state = Initializing;
}

// Called repeatedly when this Command is scheduled to run
void DriveToVisionTargetCommand::Execute()
{
	// This should move into a thread.
	this->UpdateCameraData();
	double distance = this->sensorSubsystem->GetChassisUltrasonicCenterDistance();
	double cameraAngle = 20;
	if (distance < 60 && distance > 40)
	{
		cameraAngle = 30;
	}
	else if (distance < 40)
	{
		cameraAngle = 45;
	}
	this->cameraSubsystem->SetCameraTilt(cameraAngle);

	switch (this->state)
	{
	case Initializing:
		this->state = FindingTarget;
		break;
	case FindingTarget:
		if (this->isVisionTargetPresent)
		{
			this->state = CenteringTarget;
		}
		// TODO need to figure out how to break out of here
		break;
	case CenteringTarget:
		if (abs(this->visionTargetXOffsetInPixels) < 10)
		{
			this->state = DrivingToTarget;
		} else if (this->visionTargetXOffsetInPixels < 0)
		{
			// target left of center, turn left
			this->chassis->FilteredArcade(0, -.2, false);
		}
		else
		{
			this->chassis->FilteredArcade(0, 2, false);
		}
		break;
	case DrivingToTarget:
		double rotate = .1 * this->visionTargetXOffsetInPixels;
		this->chassis->FilteredArcade(.2, rotate, false);
		break;
	}
	// camera tilt of 1 near the wall, .87 when 12' from wall
}

// Make this return true when this Command no longer needs to run execute()
bool DriveToVisionTargetCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void DriveToVisionTargetCommand::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveToVisionTargetCommand::Interrupted()
{

}

void DriveToVisionTargetCommand::UpdateCameraData()
{

}
