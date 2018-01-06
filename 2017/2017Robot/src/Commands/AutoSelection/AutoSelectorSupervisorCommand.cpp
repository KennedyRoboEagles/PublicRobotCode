#include "AutoSelectorSupervisorCommand.h"
#include <AutoSelection.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>

AutoSelectorSupervisorCommand::AutoSelectorSupervisorCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetRunWhenDisabled(true);
}

// Called just before this Command runs the first time
void AutoSelectorSupervisorCommand::Initialize() {
}

// Called repeatedly when this Command is scheduled to run
void AutoSelectorSupervisorCommand::Execute() {
	oi->UpdateAutoButtons();
	char buff[20];
	sprintf(buff, "%i", AutoSelection::GetInstance()->CurrentAuto());
	oi->GetRevDigit()->Display(buff);

}

// Make this return true when this Command no longer needs to run execute()
bool AutoSelectorSupervisorCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AutoSelectorSupervisorCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AutoSelectorSupervisorCommand::Interrupted() {

}
