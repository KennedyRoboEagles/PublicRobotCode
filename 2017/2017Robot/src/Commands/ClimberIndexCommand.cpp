#include <Commands/ClimberIndexCommand.h>

constexpr double MOTOR_POWER = 0.23;

ClimberIndexCommand::ClimberIndexCommand() {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(climberSubsystem.get());
	this->SetTimeout(3);
}

// Called just before this Command runs the first time
void ClimberIndexCommand::Initialize() {
	climberSubsystem->Stop();
}

// Called repeatedly when this Command is scheduled to run
void ClimberIndexCommand::Execute() {
	climberSubsystem->Set(MOTOR_POWER);
}

// Make this return true when this Command no longer needs to run execute()
bool ClimberIndexCommand::IsFinished() {
	return climberSubsystem->AtIndex();
}

// Called once after isFinished returns true
void ClimberIndexCommand::End() {
	climberSubsystem->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClimberIndexCommand::Interrupted() {
	climberSubsystem->Stop();
}
