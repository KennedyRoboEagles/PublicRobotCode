#include "CommandBase.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
ExampleSubsystem* CommandBase::examplesubsystem = NULL;

Chassis* CommandBase::chassis = NULL;
CompressorSubsystem* CommandBase::compressorSubsystem = NULL;
IntakeTiltSubsystem* CommandBase::intakeTiltSubsystem = NULL;
IntakeGrabberSubsystem* CommandBase::intakeGrabberSubsystem = NULL;
LEDSubsytem* CommandBase::ledSubsystem = NULL;
SensorSubsystem* CommandBase::sensorSubsystem = NULL;
ThrowerSubsystem* CommandBase::throwerSubsystem = NULL;
ThrowerElectromagnetSubsystem* CommandBase::throwerElectromagnetSubsystem = NULL;
VisionSubsystem* CommandBase::visionSubsystem = NULL;

OI* CommandBase::oi = NULL;

void CommandBase::init() {
    // Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.
	examplesubsystem = new ExampleSubsystem();
	
	sensorSubsystem = new SensorSubsystem();
	
	chassis = new Chassis();
	compressorSubsystem = new CompressorSubsystem();
	intakeGrabberSubsystem = new IntakeGrabberSubsystem();
	intakeTiltSubsystem = new IntakeTiltSubsystem();
	throwerSubsystem = new ThrowerSubsystem();
	ledSubsystem = new LEDSubsytem();
	throwerElectromagnetSubsystem = new ThrowerElectromagnetSubsystem();
	visionSubsystem = new VisionSubsystem();
	oi = new OI();
	
	SmartDashboard::PutData(chassis);
	SmartDashboard::PutData(compressorSubsystem);
	SmartDashboard::PutData(intakeGrabberSubsystem);
	SmartDashboard::PutData(intakeTiltSubsystem);
	//SmartDashboard::Putdata(ledSubsystem);
	SmartDashboard::PutData(sensorSubsystem);
	SmartDashboard::PutData(throwerSubsystem);
	SmartDashboard::PutData(throwerElectromagnetSubsystem);
	SmartDashboard::PutData(visionSubsystem);
}
