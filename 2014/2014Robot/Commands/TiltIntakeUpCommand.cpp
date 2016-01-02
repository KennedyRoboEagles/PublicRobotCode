#include "TiltIntakeUpCommand.h"

TiltIntakeUpCommand::TiltIntakeUpCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(intakeTiltSubsystem);
}

// Called just before this Command runs the first time
void TiltIntakeUpCommand::Initialize() {
	printf("[TiltIntakeUpCommand] Starting to tilt the intake up\n");
	intakeTiltSubsystem->TiltUp();
}

// Called repeatedly when this Command is scheduled to run
void TiltIntakeUpCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TiltIntakeUpCommand::IsFinished() {
	return sensorSubsystem->GetIntakeHighLimit();
}

// Called once after isFinished returns true
void TiltIntakeUpCommand::End() {
	printf("[TiltIntakeUpCommand] Intake Tilt has reached the high limit\n");
	intakeTiltSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TiltIntakeUpCommand::Interrupted() {
	printf("[TiltIntakeUpCommand] Interrupted Sopping intake tilt\n");
	intakeTiltSubsystem->Stop();
}
