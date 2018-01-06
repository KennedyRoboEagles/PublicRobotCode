#include "ResetChassisEncodersCommand.h"

ResetChassisEncodersCommand::ResetChassisEncodersCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ResetChassisEncodersCommand::Initialize() {
	sensorSubsystem->GetChassisLeftEncoder()->Reset();
	sensorSubsystem->GetChassisRightEncoder()->Reset();
}

// Called repeatedly when this Command is scheduled to run
void ResetChassisEncodersCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ResetChassisEncodersCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ResetChassisEncodersCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetChassisEncodersCommand::Interrupted() {

}
