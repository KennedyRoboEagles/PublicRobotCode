#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <Subsystems/LowerCarManipulatorSubsystem.h>
#include <string>
#include "Commands/Command.h"
#include "Subsystems/ExampleSubsystem.h"
#include "Subsystems/Chassis.h"
#include "Subsystems/SensorSubsystem.h"
#include "Subsystems/LowerTowerSubsystem.h"
#include "Subsystems/UpperTowerSubsystem.h"
#include "Subsystems/TowerSubsystem.h"
#include "Subsystems/CameraSubsystem.h"
#include "OI.h"
#include "WPILib.h"

const int MIN_AUTONOMOUS_MODE = 1;

const int NO_STEP_DRIVE_FORWARD = 1;
const int STEP_DRIVE_FORWARD = 2;
const int DO_NOTHING = 3;

const int MAX_AUTONOMOUS_MODE = 3;

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();

	static SensorSubsystem *sensorSubsystem;
	static CameraSubsystem *cameraSubsystem;


	static Chassis *chassis;
	static LowerCarManipulatorSubsystem *lowerCarManipulatorSubsystem;
	static LowerTowerSubsystem *lowerTowerSubsystem;
	static UpperTowerSubsystem *upperTowerSubsystem;
	static TowerSubsystem *towerSubsystem;

	static OI *oi;

	static int autonomousProgram;
};

#endif
