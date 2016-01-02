#include "ThrowCommand.h"

#define THROW_TIME (0.25)

ThrowCommand::ThrowCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
	this->throwTimer = new Timer();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
	this->ThrowingTime = THROW_TIME;
}

ThrowCommand::ThrowCommand(float throwingTime) {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
	this->throwTimer = new Timer();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
	this->ThrowingTime = throwingTime;
}

// Called just before this Command runs the first time
void ThrowCommand::Initialize() {
	printf("[ThrowCommand] Starting Throw with time %f\n", ThrowingTime);
	throwerSubsystem->Throw();
	this->throwTimer->Start();
}

// Called repeatedly when this Command is scheduled to run
void ThrowCommand::Execute() {
#ifdef DEBUG_PRINT
	printf("[ThrowCommand] Waiting for throw to end\n");
#endif
}

// Make this return true when this Command no longer needs to run execute()
bool ThrowCommand::IsFinished() {
	return (this->throwTimer->Get() >= ThrowingTime);
}

// Called once after isFinished returns true
void ThrowCommand::End() {
	printf("[ThrowCommand] Throw Finished\n");
	throwerSubsystem->Stop();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowCommand::Interrupted() {
	printf("[ThrowCommand] Throw Interrupted\n");
	throwerSubsystem->Stop();
	this->throwTimer->Reset();
	this->throwTimer->Stop();
}
