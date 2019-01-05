#include "MotionMagicCommand.h"

MotionMagicCommand::MotionMagicCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
}

// Called just before this Command runs the first time
void MotionMagicCommand::Initialize() {
	chassis->Stop();
	chassis->ZeroEncoders();
}

// Called repeatedly when this Command is scheduled to run
void MotionMagicCommand::Execute() {
	chassis->MotionMagicFeet(5, 5);
}

// Make this return true when this Command no longer needs to run execute()
bool MotionMagicCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MotionMagicCommand::End() {
	chassis->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MotionMagicCommand::Interrupted() {
	chassis->Stop();
}
