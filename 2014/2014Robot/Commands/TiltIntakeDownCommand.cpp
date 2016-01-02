#include "TiltIntakeDownCommand.h"

TiltIntakeDownCommand::TiltIntakeDownCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeTiltSubsystem);
}

// Called just before this Command runs the first time
void TiltIntakeDownCommand::Initialize() {
	printf("[TiltIntakeDownCommand] Starting to tilt the intake down\n");
	intakeTiltSubsystem->TiltDown();
}

// Called repeatedly when this Command is scheduled to run
void TiltIntakeDownCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TiltIntakeDownCommand::IsFinished() {
	return sensorSubsystem->GetIntakeLowLimit();
}

// Called once after isFinished returns true
void TiltIntakeDownCommand::End() {
	printf("[TiltIntakeDownCommand] The intake has reached the low limit, Stopping\n");
	intakeTiltSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltIntakeDownCommand::Interrupted() {
	printf("[TiltIntakeDownCommand] Interrupted, Stopping Tilt\n");
	intakeTiltSubsystem->Stop();
}
