#include "ZeroYawCommand.h"

ZeroYawCommand::ZeroYawCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void ZeroYawCommand::Initialize() {
	sensors->GetIMU()->ZeroYaw();
}

// Called repeatedly when this Command is scheduled to run
void ZeroYawCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ZeroYawCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void ZeroYawCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ZeroYawCommand::Interrupted() {

}
