#ifndef ROBOTMAP_H
#define ROBOTMAP_H

#include <RobotConstants.h>

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int LEFTMOTOR = 1;
// constexpr int RIGHTMOTOR = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int RANGE_FINDER_PORT = 1;
// constexpr int RANGE_FINDER_MODULE = 1;

/*
 * CAN
 */
#ifndef PRACTICE_BOT
constexpr int CHASSIS_LEFT_MASTER = 3;
constexpr int CHASSIS_LEFT_SLAVE = 4;
constexpr int CHASSIS_RIGHT_MASTER = 1;
constexpr int CHASSIS_RIGHT_SLAVE = 2;
#else
constexpr int CHASSIS_LEFT_MASTER = 3;
constexpr int CHASSIS_LEFT_SLAVE = 5;
constexpr int CHASSIS_RIGHT_MASTER = 2;
constexpr int CHASSIS_RIGHT_SLAVE = 6;
#endif
/*
 * DIO
 */
constexpr int CHASSIS_LEFT_ENCODER_A = 2;
constexpr int CHASSIS_LEFT_ENCODER_B = 3;
constexpr int CHASSIS_RIGHT_ENCODER_A = 0;
constexpr int CHASSIS_RIGHT_ENCODER_B = 1;
constexpr int CLIMBER_INDEX = 4;

/*
 * PWM
 */
constexpr int CLIMBER_CONTROLLER_0 = 0;
constexpr int CLIMBER_CONTROLLER_1 = 1;
constexpr int SHOOTER_CONTROLLER = 2;

/*
 * PDP
 */
constexpr int PDP_CHASSIS_LEFT_FRONT  = 0;
constexpr int PDP_CHASSIS_LEFT_BACK   = 1;
constexpr int PDP_CHASSIS_RIGHT_FRONT = 2;
constexpr int PDP_CHASSIS_RIGHT_BACK  = 3;
constexpr int PDP_CLIMBER_0 = 15;
constexpr int PDP_CLIMBER_1 = 14;


#endif  // ROBOTMAP_H
