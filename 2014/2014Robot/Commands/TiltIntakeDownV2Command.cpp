#include "TiltIntakeDownV2Command.h"

#define TILT_LOW_LIMIT_IGNORE_TIME (.3)

TiltIntakeDownV2Command::TiltIntakeDownV2Command() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeTiltSubsystem);
	this->timer = new Timer();
	this->timer->Reset();
}

// Called just before this Command runs the first time
void TiltIntakeDownV2Command::Initialize() {
	this->timer->Reset();
	intakeTiltSubsystem->TiltDown();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void TiltIntakeDownV2Command::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TiltIntakeDownV2Command::IsFinished() {
	if(this->timer->Get() >= TILT_LOW_LIMIT_IGNORE_TIME) {
		return false;
	}
	return sensorSubsystem->GetIntakeLowLimit();
}

// Called once after isFinished returns true
void TiltIntakeDownV2Command::End() {
	this->timer->Stop();
	intakeTiltSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltIntakeDownV2Command::Interrupted() {
	this->timer->Stop();
	intakeTiltSubsystem->Stop();
}
