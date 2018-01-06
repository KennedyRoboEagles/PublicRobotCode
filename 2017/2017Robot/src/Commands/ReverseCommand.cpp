#include "ReverseCommand.h"
#include "Util/utils.hpp"

ReverseCommand::ReverseCommand() : CommandBase("ReverseCommand") {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
	//this->controller = controller;
}

// Called just before this Command runs the first time
void ReverseCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ReverseCommand::Execute() {
	//chassis->ArcadeDrive(controller->GetRawAxis(2) * REVERSE_NERF, -controller->GetRawAxis(0) * TURN_NERF);

	double x = HandleDeadband(oi->GetController()->GetRawAxis(0), DEADBAND);
	x *= -1;

	chassis->ArcadeDrive(oi->GetController()->GetRawAxis(2) * REVERSE_NERF, x * TURN_NERF);

}

// Make this return true when this Command no longer needs to run execute()
bool ReverseCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ReverseCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReverseCommand::Interrupted() {
	chassis->Stop();
}
