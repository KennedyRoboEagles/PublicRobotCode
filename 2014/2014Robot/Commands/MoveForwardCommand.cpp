#include "MoveForwardCommand.h"

MoveForwardCommand::MoveForwardCommand(int inches, float speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->speed = speed;
	this->distance = inches;
	this->distanceTicks = distance * CHASSIS_TICKS_PER_INCH;
	this->encoderSetpoint = 0;
}

// Called just before this Command runs the first time
void MoveForwardCommand::Initialize() {
	printf("[MoveForwardCommand] Reseting Gyro\n");
	sensorSubsystem->GetHorizontalGyro()->Reset();
	this->encoderSetpoint = sensorSubsystem->GetRightDriveEncoderCount() + this->distanceTicks;
	printf("[MoveForwardCommand] Distance %i inches, Encoder Setpoint%f\n", this->distance, this->encoderSetpoint);
}

// Called repeatedly when this Command is scheduled to run
void MoveForwardCommand::Execute() {
	float angle = sensorSubsystem->GetHorizontalGyro()->GetAngle();
	float rotation = (-angle) * 0.03;
	chassis->ArcadeDrive(speed, rotation);
	
	this->delta = sensorSubsystem->GetRightDriveEncoderCount() - encoderSetpoint;
#ifdef DEBUG_PRINT
	printf("[MoveForwardCommand] Encoder delta:%f Rotation:%f\n", this->delta, angle);
#endif
}

// Make this return true when this Command no longer needs to run execute()
bool MoveForwardCommand::IsFinished() {
	if(this->delta >= 0.0) {
		return true;
	} else {
		return false;
	}
}

// Called once after isFinished returns true
void MoveForwardCommand::End() {
	printf("[MoveForwardCommand] Robot has reached the distance: %i", this->distance);
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveForwardCommand::Interrupted() {
	printf("[MoveForwardCommand] Interrupted stopping the chassis\n");
	chassis->Stop();
}
