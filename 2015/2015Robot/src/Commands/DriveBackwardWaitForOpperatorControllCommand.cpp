#include "DriveBackwardWaitForOpperatorControllCommand.h"
#include <math.h>

const float DEAD_ZONE = 0.01;

DriveBackwardWaitForOpperatorControllCommand::DriveBackwardWaitForOpperatorControllCommand(float timeOut, float speed)
{
	Requires(chassis);
	this->timer = new Timer();
	this->timeOut = timeOut;
	this->speed = -std::fabs(speed);
}

// Called just before this Command runs the first time
void DriveBackwardWaitForOpperatorControllCommand::Initialize()
{
	chassis->Stop();
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveBackwardWaitForOpperatorControllCommand::Execute()
{
	chassis->FilteredArcade(this->speed, 0.0, false);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveBackwardWaitForOpperatorControllCommand::IsFinished()
{
	return this->timer->HasPeriodPassed(this->timeOut) || this->isDriverPresent();
}

// Called once after isFinished returns true
void DriveBackwardWaitForOpperatorControllCommand::End()
{
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveBackwardWaitForOpperatorControllCommand::Interrupted()
{
	chassis->Stop();
}

bool DriveBackwardWaitForOpperatorControllCommand::isDriverPresent() {
	bool ret = true;
	ret &= oi->GetDriverStick()->GetX() >= DEAD_ZONE;
	ret &= oi->GetDriverStick()->GetY() >= DEAD_ZONE;
	ret &= oi->GetDriverStick()->GetZ() >= DEAD_ZONE;
	return ret;
}
