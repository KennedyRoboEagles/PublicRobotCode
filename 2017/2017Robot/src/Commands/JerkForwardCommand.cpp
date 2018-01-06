#include "JerkForwardCommand.h"

JerkForwardCommand::JerkForwardCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
	this->SetTimeout(0.3);
}


// Called just before this Command runs the first time
void JerkForwardCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void JerkForwardCommand::Execute() {
	chassis->TankDrive(0.15, 0.15);
}

// Make this return true when this Command no longer needs to run execute()
bool JerkForwardCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void JerkForwardCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void JerkForwardCommand::Interrupted() {

}
