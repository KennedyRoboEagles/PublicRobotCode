#include "TimedForwardCommand.h"

TimedForwardCommand::TimedForwardCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());
	this->timer = new Timer();
}

// Called just before this Command runs the first time
void TimedForwardCommand::Initialize() {
	this->timer->Start();
	chassis->ArcadeDrive(0.35,0);
}

// Called repeatedly when this Command is scheduled to run
void TimedForwardCommand::Execute() {
	chassis->TankDrive(0.13,0.13);
}

// Make this return true when this Command no longer needs to run execute()
bool TimedForwardCommand::IsFinished() {
	return timer->HasPeriodPassed(5.0);
}

// Called once after isFinished returns true
void TimedForwardCommand::End() {
	chassis->Stop();
	timer->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void TimedForwardCommand::Interrupted() {
	chassis->Stop();
	timer->Stop();
}
