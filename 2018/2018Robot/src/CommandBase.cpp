/*
 * CommandBase.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: nowir
 */

#include "CommandBase.h"
#include "Constants.h"
#include <SmartDashboard/SmartDashboard.h>
#include <DriverStation.h>

std::shared_ptr<Chassis> CommandBase::chassis;
std::shared_ptr<ElevatorSubsystem> CommandBase::elevator;
std::shared_ptr<SensorSubsystem> CommandBase::sensors;
std::shared_ptr<IntakeSubsystem> CommandBase::intake;
std::shared_ptr<LEDSubsystem> CommandBase::leds;
std::shared_ptr<OI> CommandBase::oi;

void CommandBase::InitSubsystems() {
	if(kEnableSubsystemChassis) {
		chassis = std::make_shared<Chassis>();
	} else {
		DriverStation::GetInstance().ReportWarning("Chassis is disabled");
	}

	// The intake needs to created before the elevator
	if(kEnableSubsystemIntake) {
		intake = std::make_shared<IntakeSubsystem>();
	} else {
		DriverStation::GetInstance().ReportWarning("Intake is disabled");
	}

	if(kEnableSubsystemElevator) {
		elevator = std::make_shared<ElevatorSubsystem>(intake);
	} else {
		DriverStation::GetInstance().ReportWarning("Elevator is disabled");
	}

	if(kEnableSubsystemSensors) {
		sensors = std::make_shared<SensorSubsystem>();
	} else {
		DriverStation::GetInstance().ReportWarning("Sensors is disabled");
	}

	leds = std::make_shared<LEDSubsystem>();

	oi = std::make_shared<OI>();
}
