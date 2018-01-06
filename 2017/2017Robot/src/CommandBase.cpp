#include "CommandBase.h"

#include <Commands/Scheduler.h>
#include <SmartDashboard/SmartDashboard.h>

// Initialize a single static instance of all of your subsystems. The following
// line should be repeated for each subsystem in the project.
std::unique_ptr<OI> CommandBase::oi;
std::unique_ptr<Chassis> CommandBase::chassis;
std::unique_ptr<SensorSubsystem> CommandBase::sensorSubsystem;
std::unique_ptr<ClimberSubsystem> CommandBase::climberSubsystem;
std::unique_ptr<ShooterSubsystem> CommandBase::shooterSubsystem;

void CommandBase::InitSubsystems() {

	sensorSubsystem = std::make_unique<SensorSubsystem>();

	chassis = std::make_unique<Chassis>();
	climberSubsystem = std::make_unique<ClimberSubsystem>(sensorSubsystem.get());
	shooterSubsystem = std::make_unique<ShooterSubsystem>();

	frc::SmartDashboard::PutData("chassis", chassis.get());

	oi = std::make_unique<OI>();
}

CommandBase::CommandBase(const std::string &name) :
		frc::Command(name) {

}
