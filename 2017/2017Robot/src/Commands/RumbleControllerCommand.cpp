#include <Commands/RumbleControllerCommand.h>

RumbleControllerCommand::RumbleControllerCommand(double timeout) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetTimeout(timeout);
}

// Called just before this Command runs the first time
void RumbleControllerCommand::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RumbleControllerCommand::Execute() {
	oi->GetController()->SetRumble(GenericHID::RumbleType::kLeftRumble, 1.0);
}

// Make this return true when this Command no longer needs to run execute()
bool RumbleControllerCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void RumbleControllerCommand::End() {
	oi->GetController()->SetRumble(GenericHID::RumbleType::kLeftRumble, 0);
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RumbleControllerCommand::Interrupted() {
	oi->GetController()->SetRumble(GenericHID::RumbleType::kLeftRumble, 0);
}
