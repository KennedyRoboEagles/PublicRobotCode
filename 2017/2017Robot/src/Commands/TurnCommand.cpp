#include "TurnCommand.h"
#include "Util/utils.hpp"

TurnCommand::TurnCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
}

// Called just before this Command runs the first time
void TurnCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void TurnCommand::Execute() {
	//chassis->ArcadeDrive(0, oi->GetController()->GetRawAxis(0) * TURN_NERF);
	double x = HandleDeadband(oi->GetController()->GetRawAxis(0), DEADBAND);

		chassis->ArcadeDrive(0, x * TURN_NERF);
}

// Make this return true when this Command no longer needs to run execute()
bool TurnCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void TurnCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TurnCommand::Interrupted() {
	chassis->Stop();
}
