#include <AutoSelection.h>
#include <Commands/AutoSelection/SelectPreviousCommand.h>

SelectPreviousAutoCommand::SelectPreviousAutoCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	this->SetRunWhenDisabled(true);

}

// Called just before this Command runs the first time
void SelectPreviousAutoCommand::Initialize() {
	AutoSelection::GetInstance()->PreviousAuto();
}

// Called repeatedly when this Command is scheduled to run
void SelectPreviousAutoCommand::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool SelectPreviousAutoCommand::IsFinished() {
	return true;
}

// Called once after isFinished returns true
void SelectPreviousAutoCommand::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SelectPreviousAutoCommand::Interrupted() {

}
