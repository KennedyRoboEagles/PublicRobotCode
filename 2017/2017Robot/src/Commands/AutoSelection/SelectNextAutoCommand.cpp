#include "SelectNextAutoCommand.h"
#include <AutoSelection.h>

SelectNextAutoCommand::SelectNextAutoCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void SelectNextAutoCommand::Initialize() {
	AutoSelection::GetInstance()->NextAuto();
}

// Called repeatedly when this Command is scheduled to run
void SelectNextAutoCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SelectNextAutoCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SelectNextAutoCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectNextAutoCommand::Interrupted() {

}
