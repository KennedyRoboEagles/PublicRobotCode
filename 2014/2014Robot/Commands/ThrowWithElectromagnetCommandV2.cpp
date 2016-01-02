#include "ThrowWithElectromagnetCommandV2.h"

#define THROW_TIME (2)
#define ELECTROMAGNET_OVERLAP_TIME (1.5)

ThrowWithElectromagnetCommandV2::ThrowWithElectromagnetCommandV2() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
	this->timer = new Timer();
	this->timer->Reset();
	this->timer->Stop();
}

// Called just before this Command runs the first time
void ThrowWithElectromagnetCommandV2::Initialize() {
	throwerElectromagnetSubsystem->StartThrow(ELECTROMAGNET_OVERLAP_TIME);
	throwerSubsystem->Throw();
	this->timer->Reset();
	this->timer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ThrowWithElectromagnetCommandV2::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool ThrowWithElectromagnetCommandV2::IsFinished() {
	return this->timer->Get() >= THROW_TIME;
}

// Called once after isFinished returns true
void ThrowWithElectromagnetCommandV2::End() {
	throwerSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowWithElectromagnetCommandV2::Interrupted() {
	throwerSubsystem->Stop();
}
