#include "ReverseDriveCommand.h"

ReverseDriveCommand::ReverseDriveCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
}

// Called just before this Command runs the first time
void ReverseDriveCommand::Initialize() {
	chassis->ToggeleReverseDrive();
}

// Called repeatedly when this Command is scheduled to run
void ReverseDriveCommand::Execute() {
}

// Make this return true when this Command no longer needs to run execute()
bool ReverseDriveCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ReverseDriveCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseDriveCommand::Interrupted() {

}
