#include "DriveForwardTimeCommand.h"

#define ANGLE_PROPORTIONAL_GAIN (0.03)

DriveForwardTimeCommand::DriveForwardTimeCommand(float seconds, float speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->time = seconds;
	this->speed = speed;
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void DriveForwardTimeCommand::Initialize() {
	this->timer->Reset();
	this->timer->Stop();
	
	chassis->ArcadeDrive(speed, 0);
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void DriveForwardTimeCommand::Execute() {
	//float angle = sensorSubsystem->GetHorizontalGyro()->GetAngle();
	//float rotation = (-angle) * ANGLE_PROPORTIONAL_GAIN;
	chassis->ArcadeDrive(speed, 0);
#ifdef DEBUG_PRINT
	printf("[DriveForwardTimeCommand] Time:%f\n", this->timer->Get());
#endif
	//printf("[DriveForwardTimeCommand] Rotation:%f\n", angle);
}

// Make this return true when this Command no longer needs to run execute()
bool DriveForwardTimeCommand::IsFinished() {
	return this->timer->Get() >= time;
}

// Called once after isFinished returns true
void DriveForwardTimeCommand::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void DriveForwardTimeCommand::Interrupted() {
	this->cleanUp();
}

void DriveForwardTimeCommand::cleanUp() {
	this->timer->Stop();
	this->timer->Reset();
	chassis->Stop();
}
