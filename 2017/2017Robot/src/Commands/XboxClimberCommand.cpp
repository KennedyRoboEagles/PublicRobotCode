#include "XboxClimberCommand.h"
#include "../Subsystems/ClimberSubsystem.h"
#include <Util/utils.hpp>

XboxClimberCommand::XboxClimberCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(climberSubsystem.get());
}

// Called just before this Command runs the first time
void XboxClimberCommand::Initialize() {
	 climberSubsystem->Stop();
}

// Called repeatedly when this Command is scheduled to run
void XboxClimberCommand::Execute() {
	double y = HandleDeadband(oi->GetController()->GetRawAxis(5), 0.11);
	y *= -1;
	if(y < 0) y = 0;

	climberSubsystem->Set(y);
}

// Make this return true when this Command no longer needs to run execute()
bool XboxClimberCommand::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void XboxClimberCommand::End() {
	 climberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void XboxClimberCommand::Interrupted() {
	 climberSubsystem->Stop();
}
