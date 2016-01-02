#include "DriveForwardToObject.h"
#include <cmath>

/*
 * Drives straight ahead until the object in front of the robot is at the prescribed distance.
 */
DriveForwardToObject::DriveForwardToObject(double distance)
{
	Requires(chassis);
	this->distance = distance;
}

// Called just before this Command runs the first time
void DriveForwardToObject::Initialize()
{

}

// Called repeatedly when this Command is scheduled to run
void DriveForwardToObject::Execute()
{
	chassis->GetDrive()->ArcadeDrive(.25, 0);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardToObject::IsFinished()
{
	return abs(this->sensorSubsystem->GetChassisUltrasonicCenterDistance() - this->distance) < deltaInches;
}

// Called once after isFinished returns true
void DriveForwardToObject::End()
{

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardToObject::Interrupted()
{

}
