#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
SensorSubsystem* CommandBase::sensorSubsystem = NULL;
CameraSubsystem *CommandBase::cameraSubsystem = NULL;
Chassis *CommandBase::chassis = NULL;
LowerCarManipulatorSubsystem *CommandBase::lowerCarManipulatorSubsystem = NULL;
LowerTowerSubsystem *CommandBase::lowerTowerSubsystem= NULL;
UpperTowerSubsystem *CommandBase::upperTowerSubsystem = NULL;
TowerSubsystem *CommandBase::towerSubsystem = NULL;

OI* CommandBase::oi = NULL;

int CommandBase::autonomousProgram = MIN_AUTONOMOUS_MODE;

CommandBase::CommandBase(char const *name) : Command(name) {}

CommandBase::CommandBase() : Command() {}

void CommandBase::init() {
	/*
	 * Stand alone subsystems
	 */

	sensorSubsystem = new SensorSubsystem();
	cameraSubsystem = new CameraSubsystem();

	/*
	 * Subsystems that could/take dependence on the above subsystems
	 */
	chassis = new Chassis();
	lowerCarManipulatorSubsystem = new LowerCarManipulatorSubsystem(sensorSubsystem);
	lowerTowerSubsystem = new LowerTowerSubsystem(sensorSubsystem);
	upperTowerSubsystem = new UpperTowerSubsystem(sensorSubsystem);
	towerSubsystem = new TowerSubsystem(sensorSubsystem);

	/*
	 * The operator interface
	 */
	oi = new OI();

	SmartDashboard::PutData(sensorSubsystem);
	SmartDashboard::PutData(cameraSubsystem);
	SmartDashboard::PutData(chassis);
	SmartDashboard::PutData(lowerCarManipulatorSubsystem);
	SmartDashboard::PutData(lowerTowerSubsystem);
	SmartDashboard::PutData(upperTowerSubsystem);
	SmartDashboard::PutData(towerSubsystem);
}
