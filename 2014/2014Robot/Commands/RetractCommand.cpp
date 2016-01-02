#include "RetractCommand.h"

RetractCommand::RetractCommand() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	Requires(throwerSubsystem);
}

// Called just before this Command runs the first time
void RetractCommand::Initialize() {
	printf("[RetractCommand] Retracting Thrower\n");
	throwerSubsystem->Retract();
}

// Called repeatedly when this Command is scheduled to run
void RetractCommand::Execute() {
#ifdef DEBUG_PRINT
	printf("[RetractCommand] Waiting for thrower to retract\n");
#endif 
}

// Make this return true when this Command no longer needs to run execute()
bool RetractCommand::IsFinished() {
	return sensorSubsystem->GetThrowerLowLimt();
}

// Called once after isFinished returns true
void RetractCommand::End() {
	printf("[RetractCommand] Thrower Retracted\n");
	throwerSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RetractCommand::Interrupted() {
	printf("[RetractCommand] Thrower Interrupted\n");
	throwerSubsystem->Stop();
}
