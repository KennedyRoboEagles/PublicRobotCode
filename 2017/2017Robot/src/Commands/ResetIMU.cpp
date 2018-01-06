#include "ResetIMU.h"

ResetIMU::ResetIMU() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
}

// Called just before this Command runs the first time
void ResetIMU::Initialize() {
	sensorSubsystem->GetIMU()->ZeroYaw();
}

// Called repeatedly when this Command is scheduled to run
void ResetIMU::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ResetIMU::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ResetIMU::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ResetIMU::Interrupted() {

}
