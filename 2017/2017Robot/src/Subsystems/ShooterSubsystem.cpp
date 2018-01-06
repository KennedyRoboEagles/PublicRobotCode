#include "ShooterSubsystem.h"
#include "../RobotMap.h"
#include <Jaguar.h>

constexpr double SHOOT_POWER = 1.0;

ShooterSubsystem::ShooterSubsystem() : Subsystem("ShooterSubsystem") {
	this->jag = new Jaguar(SHOOTER_CONTROLLER);
}

void ShooterSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void ShooterSubsystem::Shoot() {
	this->jag->Set(SHOOT_POWER);
}

void ShooterSubsystem::Stop() {
	this->jag->Set(0);
}
