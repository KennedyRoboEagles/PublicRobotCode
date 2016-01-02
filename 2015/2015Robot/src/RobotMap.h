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
const int OI_JOYSTICK_TEST_TOWER = 3;
const int OI_JOYSTICK_TEST_GRABBER = 4;

/*
 * Buttons Driver Stick
 */
const int OI_BUTTON_DRIVER_AUTO_SELECT = 11;

/*
 * Buttons 2nd Driver Stick
 */
const int OI_BUTTON_SECOND_DRIVER_LOWER = 1;
const int OI_BUTTON_SECOND_DRIVER_STACK = 2;
const int OI_BUTTON_SECOND_DRIVER_2ND_TOTE = 3;
const int OI_BUTTON_SECOND_DRIVER_OPEN_NARROW = 4;
const int OI_BUTTON_SECOND_DROVER_ACQUIRE = 5;
const int OI_BUTTON_SECOND_DRIVER_OPEN_WIDE = 6;

const int OI_BUTTON_SECOND_DRIVER_BIN_CLEAR_4_STACK = 8;
const int OI_BUTTON_SECOND_DRIVER_CLEAR_PLAYER_STATION = 9;

const int OI_BUTTON_SECOND_DRIVER_LOAD_RECYLE_BIN = 7;
const int OI_BUTTON_SECOND_DRIVER_PICK_NEXT_TOTE = 10;
const int OI_BUTTON_SECOND_DRICER_PICK_UP_LAST_TOTE = 11;

/*
 * Buttons Test Tower
 */
const int OI_BUTTON_TEST_TOWER_CLEAR_PLAYERSTATION = 1;
const int OI_BUTTON_TEST_TOWER_LOWER_TOTE = 2;
const int OI_BUTTON_TEST_TOWER_MOVE_TO_BOTTOM = 3;
const int OI_BUTTON_TEST_TOWER_MOVE_TO_BOTTOM_MOVEMENT = 4;
const int OI_BUTTON_TEST_TOWER_MOVE_TO_PICK_UP = 5;
const int OI_BUTTON_TEST_TOWER_MOVE_2ND_TOTE= 6;
const int OI_BUTTON_TEST_TOWER_MOVE_TO_STACK_POSITION = 7;

/*
 * Button Test Grabber
 */
const int OI_BUTTON_TEST_GRABBER_ACQUIRE_TOTE = 1;
const int OI_BUTTON_TEST_GRABBER_CLOSE_FOR_BIN= 2;
const int OI_BUTTON_TEST_GRABBER_CLOSE_FOR_NARROW_TOTE = 3;
const int OI_BUTTON_TEST_GRABBER_OPEN_FOR_NARROW_TOTE = 4;
const int OI_BUTTON_TEST_GRABBER_RELEASE_TOTE = 5;
const int OI_BUTTON_TEST_GRABBER_OPEN_FOR_WIDE = 6;

const int OI_BUTTON_TEST_GRABBER_MOVE_INWARD = 10;
const int OI_BUTTON_TEST_GRABBER_MOVE_OUTWARD = 11;


/*
 * Digital inputs
 */

// 0-9 are the roboRio ports

// Tower

const int TOWER_LIMIT_LOW = 0;

const int LOWER_CAR_VERTICAL_POSITION_ENCODER_A = 1;
const int LOWER_CAR_VERTICAL_POSITION_ENCODER_B = 2;
const int UPPER_CAR_VERTICAL_POSITION_ENCODER_A = 17;
const int UPPER_CAR_VERTICAL_POSITION_ENCODER_B = 18;



// Tower-car integration
const int LOWER_CAR_VERTICAL_LIMIT_HIGH = 5;
const int UPPER_CAR_VERTICAL_LIMIT_HIGH = 14;

const int TOTE_DETECTION = 21;

// Lower car
const int LOWER_CAR_MANIPULATOR_ENCODER_A = 8;
const int LOWER_CAR_MANIPULATOR_ENCODER_B = 9;

// Upper car

// These start at 10 so that they all appear on the mxp

const int UPPER_CAR_MANIPULATOR_CLOSED_LIMIT = 10;
const int UPPER_CAR_MANIPULATOR_OPEN_LIMIT = 11;
const int UPPER_CAR_MANIPULATOR_ENCODER_A = 12;
const int UPPER_CAR_MANIPULATOR_ENCODER_B = 13;

// Drive train
// These may not be necessary if we get the nav sensor to do it for us.
const int CHASSIS_LEFT_ENCODER_A = 15;
const int CHASSIS_LEFT_ENCODER_B = 16;
const int CHASSIS_RIGHT_ENCODER_A = 3;
const int CHASSIS_RIGHT_ENCODER_B = 4;
const int CHASSIS_CENTER_ENCODER_A = 6;
const int CHASSIS_CENTER_ENCODER_B = 7;

/*
 *	PWM
 */
const int CHASSIS_RIGHT_JAGUAR = 0;
const int CHASSIS_LEFT_JAGUAR = 1;
const int CHASSIS_CENTER_JAGUAR = 2;
const int CAMERA_TILT_SERVO = 3;
const int LOWER_TOWER_DOG_GEAR_SERVO = 4;
const int COUNTERWEIGHT_JAGUAR = 7;


/*
 * CAN Bus ID
 */
const int TOWER_UCAR_JAGUAR = 2;
const int TOWER_LCAR_JAGUAR = 5;
const int UCAR_MANIPULATOR_JAGUAR = 3;
const int LCAR_MANIPULATOR_JAGUAR = 4;

/*
 *	PCM
 */

const int CAMERA_LED_RING_CHANNEL = 7;


/*
 * Analog
 */
const int CHASSIS_ULTRASONIC_LEFT = 0;
const int CHASSIS_ULTRASONIC_RIGHT = 1;
const int CHASSIS_ULTRASONIC_CENTER = 2;
const int TOWER_LCAR_FORCE_SENSOR = 3;
const int TOWER_UCAR_FORCE_SENSOR = 4;


/*
 * Power Distribution Panel Motor Assignments
 */

const int LEFT_DRIVE_PDP_CHANNEL = 0;
const int RIGHT_DRIVE_PDP_CHANNEL = 1;
const int CENTER_DRIVE_PDP_CHANNEL = 6;
const int TOWER_UPPER_CAR_PDP_CHANNEL = 3;
const int TOWER_LOWER_CAR_PDP_CHANNEL = 4;
const int UPPER_CAR_MANIPULATOR_PDP_CHANNEL = 5;
const int LOWER_CAR_MANIPULATOR_PDP_CHANNEL = 2;

#endif
