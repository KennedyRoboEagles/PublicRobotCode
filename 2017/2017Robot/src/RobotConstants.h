/*
 * RobotConstants.h
 *
 *  Created on: Jan 17, 2017
 *      Author: Ryan
 */

#ifndef SRC_ROBOTCONSTANTS_H_
#define SRC_ROBOTCONSTANTS_H_

#include <math.h>

//Comment this out to selcet the 2017 Competition Robot
//Otherwise this will alter the robot program to run on the 2017 Practice Robot.
//#define PRACTICE_BOT

//Uncomment to enable support for IMU
//#define ENABLE_IMU
//#define SELECT_NAVX


/*
 * All units are in some form of ft
 */

constexpr double kMAX_VELOCITY = 16.2;
constexpr double kMAX_ACCELERATION = 6.4;
constexpr double kMAX_JERK = 10;

constexpr double DEFAULT_MAX_ALLOWED_VELOCITY = 5.0;
constexpr double DEFAULT_MAX_ALLOWED_ACCELERATION = 3.5;
constexpr double DEFAULT_MAX_ALLOWED_JERK = 20.0;

#ifdef PRACTICE_BOT
constexpr double kWHEELBASE_WIDTH = 26.5/12.0;
constexpr double kCHASSIS_WIDTH = 31.5/12.0;
constexpr double kCHASSIS_LENGTH = 23.0/12.0;
constexpr double kCHASSIS_BUMBER = 0;//3.2/12.0;
#else
constexpr double kWHEELBASE_WIDTH = 27.54999/12.0;
constexpr double kCHASSIS_WIDTH = 31.5/12.0;
constexpr double kCHASSIS_LENGTH = 28.25/12.0;
constexpr double kCHASSIS_BUMBER = 3.2/12.0;
#endif

constexpr double kENCODER_TICKS = 120;
constexpr double kWHEEL_RADIUS = 3.0;
constexpr double kWHEEL_CIRCUMFERENCE = M_PI*2*kWHEEL_RADIUS/12.0;
constexpr double kCHASSIS_DISTANCE_PER_PULSE = kWHEEL_CIRCUMFERENCE/kENCODER_TICKS;

constexpr double kDEFAULT_TURN_TIMEOUT = 3;

// Joystick inputs less than this value are considered zero.
constexpr double kJOYSTICK_DEADBAND = 0.05;

constexpr double TURN_NERF = 0.67;
constexpr double THROTTLE_NERF = 0.8;
constexpr double REVERSE_NERF = 0.8;

constexpr double DEADBAND = .15; //deadband for the xbox joysticks present in ThrottleCommand, ReverseCommand, and TurnCommand.

#endif /* SRC_ROBOTCONSTANTS_H_ */
