#include "ClimberSubsystem.h"
#include "../RobotMap.h"
#include <Talon.h>
#include <Commands/Subsystem.h>
#include <Commands/XboxClimberCommand.h>

using namespace frc;

ClimberSubsystem::ClimberSubsystem(SensorSubsystem *sensorSubsystem) : Subsystem("ClimberSubsystem") {
	this->controller0 = new Talon(CLIMBER_CONTROLLER_0);
	this->controller1 = new Talon(CLIMBER_CONTROLLER_1);
	this->sensorSubsystem = sensorSubsystem;
}

void ClimberSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	SetDefaultCommand(new XboxClimberCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ClimberSubsystem::Stop() {
	this->Set(0);
}

void ClimberSubsystem::Set(double value) {
	this->controller0->Set(value);
	this->controller1->Set(value);
}

bool ClimberSubsystem::AtIndex() {
	return sensorSubsystem->GetClimberIndex();
}
