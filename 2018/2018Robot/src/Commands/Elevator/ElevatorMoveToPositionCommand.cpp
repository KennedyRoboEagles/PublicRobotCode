#include "ElevatorMoveToPositionCommand.h"

constexpr double kTolerance = 0.5;

ElevatorMoveToPositionCommand::ElevatorMoveToPositionCommand(double height) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(elevator.get());
	goal_ = height;
	done_ = false;
}

// Called just before this Command runs the first time
void ElevatorMoveToPositionCommand::Initialize() {
	elevator->Stop();
	done_ = false;
}

// Called repeatedly when this Command is scheduled to run
void ElevatorMoveToPositionCommand::Execute() {
	double error = goal_ - elevator->GetPosition();
	if (error < fabs(kTolerance)) {
		done_ = true;
	} else {
		if(error < 0) {
			elevator->Down();
		} else {
			elevator->Up();
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ElevatorMoveToPositionCommand::IsFinished() {
	return done_ || elevator->IsAtBottom() || elevator->IsAtTop();
}

// Called once after isFinished returns true
void ElevatorMoveToPositionCommand::End() {
	elevator->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ElevatorMoveToPositionCommand::Interrupted() {
	elevator->Stop();
}
