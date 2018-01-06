#include <Commands/ClimberControlCommand.h>
#include <Util/utils.hpp>
#include <RobotConstants.h>

//Note: We need to require the chassis when using the driving joystick
ClimberControlCommand::ClimberControlCommand(Joystick* stick, bool requireChassis) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(climberSubsystem.get());

	if(requireChassis) {
		Requires(chassis.get());
	}
	this->stick = stick;
}

// Called just before this Command runs the first time
void ClimberControlCommand::Initialize() {
	climberSubsystem->Stop();
}

// Called repeatedly when this Command is scheduled to run
void ClimberControlCommand::Execute() {
	double y = HandleDeadband(stick->GetY(), kJOYSTICK_DEADBAND);
	y *= -1;
	if(y < 0) y = 0;

	climberSubsystem->Set(y);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberControlCommand::IsFinished() {
	//return climberSubsystem->AtIndex();
	return false;
}

// Called once after isFinished returns true
void ClimberControlCommand::End() {
	climberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberControlCommand::Interrupted() {
	climberSubsystem->Stop();
}
