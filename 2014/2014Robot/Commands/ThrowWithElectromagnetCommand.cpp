#include "ThrowWithElectromagnetCommand.h"

#define THROWER_DELAY (2)
#define THROWER_TIME (1)
#define ELECTROMAGNET_TIMEOUT (3)

ThrowWithElectromagnetCommand::ThrowWithElectromagnetCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
	this->throwTimer = new Timer();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
	this->throwTime = THROWER_TIME;
	this->throwDelay = THROWER_DELAY;
	this->electromagnetTime = ELECTROMAGNET_TIMEOUT;
	this->isElectromagnetOn = false;
}
ThrowWithElectromagnetCommand::ThrowWithElectromagnetCommand(float throwTime, float electromagnetTime) {
	Requires(throwerSubsystem);
	this->throwTimer = new Timer();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
	this->throwTime = throwTime;
	this->electromagnetTime = electromagnetTime;
	this->isElectromagnetOn = false;
}
// Called just before this Command runs the first time
void ThrowWithElectromagnetCommand::Initialize() {
	printf("[ThrowWithElectromagnetCommand] Starting Throw, Throw Time:%f Electromagnet Time:%f\n", throwTime, electromagnetTime);
	//throwerSubsystem->Throw();
	throwerSubsystem->TurnOnElectromagenet();
	this->isElectromagnetOn = true;
	this->throwTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ThrowWithElectromagnetCommand::Execute() {
	if(this->throwTimer->Get() >= throwDelay) {
		throwerSubsystem->Throw();
	}
	if(this->throwTimer->Get() >= electromagnetTime && isElectromagnetOn) {
		printf("[ThrowWithElectromagnetCommand] Turning Off Electromagnet\n");
		throwerSubsystem->TurnOffElectromagnet();
		this->isElectromagnetOn = false;
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ThrowWithElectromagnetCommand::IsFinished() {
	float fullThrowTime = throwTime + throwDelay;
	return (this->throwTimer->Get() >= fullThrowTime);
}

// Called once after isFinished returns true
void ThrowWithElectromagnetCommand::End() {
	printf("[ThrowWithElectromagnetCommand] Throw Finished\n");
	throwerSubsystem->Stop();
	throwerSubsystem->TurnOffElectromagnet();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowWithElectromagnetCommand::Interrupted() {
	printf("[ThrowWithElectromagnetCommand] Throw Interrupted\n");
	throwerSubsystem->Stop();
	throwerSubsystem->TurnOffElectromagnet();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
}

