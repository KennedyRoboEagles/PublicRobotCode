#include "HDriveWithJoystickCommand.h"
#include <math.h>

const float DEAD_ZONE_X = 0.001;
const float DEAD_ZONE_Y = 0.001;
const float DEAD_ZONE_Z = 0.001;
const float DEFAULT_Z_FILTER_GAIN = 0.8;


HDriveWithJoystickCommand::HDriveWithJoystickCommand()
{
	Requires(chassis);
	//this->zFilter = DaisyFilter::SinglePoleIIRFilter(0.8);
	this->zFilter = NULL;
}

// Called just before this Command runs the first time
void HDriveWithJoystickCommand::Initialize()
{
	chassis->Stop();
	chassis->ResetFilters();
	float zFilterGain = SmartDashboard::GetBoolean("H-Drive Filter Z Gain", DEFAULT_Z_FILTER_GAIN);
	if(NULL != zFilter) {
		delete zFilter;
	}
	printf("HDrive Z-Filter Gain: %f\n", zFilterGain);
	this->zFilter = DaisyFilter::SinglePoleIIRFilter(zFilterGain);

}

// Called repeatedly when this Command is scheduled to run
void HDriveWithJoystickCommand::Execute()
{
	float x = oi->GetDriverStick()->GetX();
	float y = oi->GetDriverStick()->GetY();
	float z = oi->GetDriverStick()->GetZ();

	if(DEAD_ZONE_X > fabs(x)) {
		x = 0.0;
	}

	if(DEAD_ZONE_Y > fabs(y)) {
		y = 0.0;
	}

	if(DEAD_ZONE_Z > fabs(z)) {
		z  = 0.0;
	}


	float filteredZ = zFilter->Calculate(z);

	y = -y;
	filteredZ = -filteredZ;
	filteredZ = filteredZ * 0.9;
	chassis->GetDrive()->ArcadeDrive(y, filteredZ);
	//chassis->FilteredArcade(y, filteredZ, false);
	chassis->GetCenterSpeedController()->Set(x);
	//chassis->FilteredCenter(x);

	SmartDashboard::PutNumber("Drive X", x);
	SmartDashboard::PutNumber("Drive Y", y);
	SmartDashboard::PutNumber("Drive Z", z);
}

// Make this return true when this Command no longer needs to run execute()
bool HDriveWithJoystickCommand::IsFinished()
{
	return false;
}

// Called once after isFinished returns true
void HDriveWithJoystickCommand::End()
{
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void HDriveWithJoystickCommand::Interrupted()
{
	chassis->Stop();
}
