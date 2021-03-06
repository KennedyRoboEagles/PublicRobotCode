#include "CommandBase.h"
#include "Commands/Scheduler.h"

CommandBase::CommandBase(const char *name) : Command(name) {
}

CommandBase::CommandBase() : Command() {
}

// Initialize a single static instance of all of your subsystems to NULL
PizzaBoxSubsystem* CommandBase::pizzaBoxSubsystem = NULL;
SensorSubsystem* CommandBase::sensorSubsystem = NULL;
ShooterTiltSubsystem* CommandBase::shooterTiltSubsystem = NULL;
Chassis *CommandBase::chassis = NULL;
ShooterSubsystem* CommandBase::shooterSubsystem = NULL;
VisionSubsystem* CommandBase::visionSubsystem = NULL;
VisionSubsystemV2* CommandBase::visionSubsystemV2 = NULL;
LEDSubsystem* CommandBase::ledSubsystem = NULL;
KickerSubsystem* CommandBase::kickerSubsystem = NULL;
LcdDisplaySubsystem* CommandBase::lcdDisplaySubsystem = NULL;
FrisbeePanSubsystem* CommandBase::frisbeePanSubsystem = NULL;

OI* CommandBase::oi = NULL;

void CommandBase::init() {
	// Sensor subsystem must be instantiated first.
	sensorSubsystem = new SensorSubsystem();
	visionSubsystem = new VisionSubsystem();
	visionSubsystemV2 = new VisionSubsystemV2();
	ledSubsystem = new LEDSubsystem();
	lcdDisplaySubsystem = new LcdDisplaySubsystem();

	// These subsystems can take dependencies on systems above.
	pizzaBoxSubsystem = new PizzaBoxSubsystem(sensorSubsystem, ledSubsystem);
	chassis = new Chassis();
	shooterTiltSubsystem = new ShooterTiltSubsystem();
	shooterSubsystem = new ShooterSubsystem();
	kickerSubsystem = new KickerSubsystem(pizzaBoxSubsystem, sensorSubsystem);
	frisbeePanSubsystem = new FrisbeePanSubsystem(sensorSubsystem);
	
	oi = new OI();
}
