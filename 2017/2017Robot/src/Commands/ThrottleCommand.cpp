#include "ThrottleCommand.h"
#include "Util/utils.hpp"

#include <XboxJoystickMapping.h>

ThrottleCommand::ThrottleCommand() : CommandBase("ThrottleCommand"){
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
//	this->controller = controller;
}

// Called just before this Command runs the first time
void ThrottleCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ThrottleCommand::Execute() {
	//chassis->ArcadeDrive(-controller->GetRawAxis(3) * THROTTLE_NERF, controller->GetRawAxis(0) * TURN_NERF);

	double x = HandleDeadband(oi->GetController()->GetRawAxis(0), DEADBAND);
	double y = -oi->GetController()->GetRawAxis(3);

	if (oi->GetController()->GetRawButton(LeftBumper)) {
		y *= 0.3;
	} else {
		y *= THROTTLE_NERF;
	}

	chassis->ArcadeDrive(y, x * TURN_NERF);
}

// Make this return true when this Command no longer needs to run execute()
bool ThrottleCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void ThrottleCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrottleCommand::Interrupted() {
	chassis->Stop();
}
