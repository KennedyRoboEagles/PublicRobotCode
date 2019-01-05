#include "ElevatorDownCommand.h"

ElevatorDownCommand::ElevatorDownCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevator.get());
}

// Called just before this Command runs the first time
void ElevatorDownCommand::Initialize() {
	elevator->Stop();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorDownCommand::Execute() {
	elevator->Down();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorDownCommand::IsFinished() {
	return elevator->IsAtBottom();
}

// Called once after isFinished returns true
void ElevatorDownCommand::End() {
	elevator->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorDownCommand::Interrupted() {
	elevator->Stop();
}
