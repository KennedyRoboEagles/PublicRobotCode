#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include "Commands/Command.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/CompressorSubsystem.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/IntakeTiltSubsystem.h"
#include "Subsystems/IntakeGrabberSubsystem.h"
#include "Subsystems/LEDSubsytem.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/ThrowerSubsystem.h"
#include "Subsystems/ThrowerElectromagnetSubsystem.h"
#include "Subsystems/VisionSubsystem.h"
#include "OI.h"


/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command {
public:
	CommandBase(const char *name);
	CommandBase();
	static void init();
	// Create a single static instance of all of your subsystems
	static ExampleSubsystem *examplesubsystem;
	
	static Chassis *chassis;
	static CompressorSubsystem *compressorSubsystem;
	static IntakeGrabberSubsystem *intakeGrabberSubsystem;
	static IntakeTiltSubsystem *intakeTiltSubsystem;
	static LEDSubsytem *ledSubsystem;
	static SensorSubsystem *sensorSubsystem;
	static ThrowerSubsystem *throwerSubsystem;
	static ThrowerElectromagnetSubsystem *throwerElectromagnetSubsystem;
	static VisionSubsystem *visionSubsystem;

	static OI *oi;
};

#endif
