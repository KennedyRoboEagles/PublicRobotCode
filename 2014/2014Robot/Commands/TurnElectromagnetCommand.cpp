#include "TurnElectromagnetCommand.h"

TurnElectromagnetCommand::TurnElectromagnetCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
}

// Called just before this Command runs the first time
void TurnElectromagnetCommand::Initialize() {
	printf("[TurnElectromagnetCommand] Turning Electromagnet on\n");
	throwerSubsystem->TurnOnElectromagenet();
}

// Called repeatedly when this Command is scheduled to run
void TurnElectromagnetCommand::Execute() {
	
}

// Make this return true when this Command no longer needs to run execute()
bool TurnElectromagnetCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnElectromagnetCommand::End() {
	printf("[TurnElectromagnetCommand] Turning Electromagnet off\n");
	throwerSubsystem->TurnOffElectromagnet();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnElectromagnetCommand::Interrupted() {
	printf("[TurnElectromagnetCommand] Turning Electromagnet off\n");
	throwerSubsystem->TurnOffElectromagnet();
}
