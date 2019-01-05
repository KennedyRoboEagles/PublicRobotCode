#include "ElevatorUpCommand.h"

ElevatorUpCommand::ElevatorUpCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevator.get());
}

// Called just before this Command runs the first time
void ElevatorUpCommand::Initialize() {
	elevator->Stop();
}

// Called repeatedly when this Command is scheduled to run
void ElevatorUpCommand::Execute() {
	elevator->Up();
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorUpCommand::IsFinished() {
	return elevator->IsAtTop();
}

// Called once after isFinished returns true
void ElevatorUpCommand::End() {
	elevator->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorUpCommand::Interrupted() {
	elevator->Stop();
}
