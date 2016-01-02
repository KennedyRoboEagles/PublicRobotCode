#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include "WPILib.h"

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
//const int LEFTMOTOR = 1;
//const int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
//const int RANGE_FINDER_PORT = 1;
//const int RANGE_FINDER_MODULE = 1;


/*
 * Joysticks
 *
 */

const int OI_JOYSTICK_DRIVER = 0;
const int OI_JOYSTICK_SECOND_DRIVER = 1;
const int OI_JOYSTICK_TEST = 3;
const int OI_JOYSTICK_TEST_TWO = 4;


/*
 *	PWM
 */
const int CHASSIS_RIGHT_JAGUAR = 0;
const int CHASSIS_LEFT_JAGUAR = 1;
const int CHASSIS_CENTER_JAGUAR = 2;

#endif
