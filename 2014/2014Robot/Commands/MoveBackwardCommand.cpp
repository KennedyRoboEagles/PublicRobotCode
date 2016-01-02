#include "MoveBackwardCommand.h"

MoveBackwardCommand::MoveBackwardCommand(int inches, float speed) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(chassis);
	this->speed = speed;
	this->distance = inches;
	this->distanceTicks = distance * CHASSIS_TICKS_PER_INCH;
}

// Called just before this Command runs the first time
void MoveBackwardCommand::Initialize() {
	printf("[MoveBackwardCommand] Reseting Gyro\n");
	sensorSubsystem->GetHorizontalGyro()->Reset();
	this->encoderSetpoint = sensorSubsystem->GetRightDriveEncoderCount() - this->distanceTicks;
	printf("[MoveBackwardCommand] Distance %i inches, Encoder Setpoint%f\n", this->distance, this->encoderSetpoint);
}

// Called repeatedly when this Command is scheduled to run
void MoveBackwardCommand::Execute() {
	float angle = sensorSubsystem->GetHorizontalGyro()->GetAngle();
	float rotation = (-angle) * 0.03;
	chassis->ArcadeDrive(speed, rotation);
	
	this->delta = sensorSubsystem->GetRightDriveEncoderCount() + encoderSetpoint;
#ifdef DEBUG_PRINT
	printf("[MoveBackwardCommand] Encoder delta:%f Rotation:%f\n", this->delta, angle);
#endif
}

// Make this return true when this Command no longer needs to run execute()
bool MoveBackwardCommand::IsFinished() {
	if(this->delta >= 0.0) {
			return true;
		} else {
			return false;
		}
}

// Called once after isFinished returns true
void MoveBackwardCommand::End() {
	printf("[MoveForwardCommand] Robot has reached the distance: %i", this->distance);
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveBackwardCommand::Interrupted() {
	printf("[MoveForwardCommand] Interrupted stopping the chassis\n");
	chassis->Stop();
}
