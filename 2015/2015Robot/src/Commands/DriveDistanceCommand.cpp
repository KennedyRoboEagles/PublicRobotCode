#include "DriveDistanceCommand.h"
#include <cmath>

const float P_GAIN = 0.05;
const float ANGLE_P_GAIN = 0.02;

const float INCHES_PRECISION = 0.25;

DriveDistanceCommand::DriveDistanceCommand(float distance) {
	Requires(chassis);
	this->distance = distance;
	this->filter = NULL;
}

// Called just before this Command runs the first time
void DriveDistanceCommand::Initialize() {
	sensorSubsystem->GetIMU()->ZeroYaw();
	sensorSubsystem->GetLeftDriveEncoder()->Reset();
	if(this->filter != NULL) {
		delete this->filter;
	}
	this->filter = DaisyFilter::SinglePoleIIRFilter(0.8);
}

// Called repeatedly when this Command is scheduled to run
void DriveDistanceCommand::Execute() {
	float angle = sensorSubsystem->GetIMU()->GetYaw();
	float rotate = ANGLE_P_GAIN * angle;
	//TODO Limit rotate

	this->error = this->distance - sensorSubsystem->GetLeftDriveEncoder()->GetDistance();
	float move = P_GAIN * error;

	if(fabs(move) > 0.45) {
		if(move > 0) {
			move = 0.45;
		} else {
			move = -0.45;
		}
	} else if(fabs(move) < 0.3) {
		if(move > 0) {
			move = 0.3;
		} else {
			move = -0.3;
		}
	}

	chassis->GetDrive()->ArcadeDrive(move, rotate, false);
	printf("Error %f, Move %f, Rotate %f\n", this->error, move, rotate);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveDistanceCommand::IsFinished(){
	return fabs(this->error) < INCHES_PRECISION;
}

// Called once after isFinished returns true
void DriveDistanceCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveDistanceCommand::Interrupted() {
	chassis->Stop();
}
