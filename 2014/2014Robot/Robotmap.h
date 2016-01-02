#ifndef ROBOTMAP_H
#define ROBOTMAP_H

// #define	DEBUG_PRINT	(1)

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
 
// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// #define LEFTMOTOR 1
// #define RIGHTMOTOR 2

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// #define RANGE_FINDER_PORT 1
// #define RANGE_FINDER_MODULE 1

/*
 * Joysticks
 */
#define JOYSTICK_PORT_DRIVER	1
#define JOYSTICK_PORT_DRIVER_TWO 2
#define JOYSTICK_PORT_TEST		3
#define JOYSTICK_PORT_TEST2		4

/*
 * Driver Joystick Buttons
 */
#define BUTTON_DRIVER_THROW				1
#define BUTTON_DRIVER_TILT_INTAKE_DOWN	2
#define BUTTON_DRIVER_TILT_INTAKE_UP	3
#define BUTTON_DRIVER_OPEN_INTAKE		4
#define BUTTON_DRIVER_CLOSE_INTAKE		5
#define	BUTTON_PREVENT_AUTO_BALL_INTAKE	6
#define BUTTON_DRIVER_INVERT_JOYSTICK	7
#define BUTTON_DRIVER_THROW_RESET		8
#define BUTTON_DRIVER_LOAD_AND_THROW	10
#define BUTTON_DRIVER_SOFT_THROW		11

/*
 * Driver 2
 */
//#define BUTTON_DRIVER_TWO_THROW 			1
//#define BUTTON_DRIVER_TWO_THROW_RESET		10
//#define BUTTON_DRIVER_TWO_TEST_SWAP 		2
//#define BUTTON_DRIVER_TWO_TEST_SWAP_RESET 	3
//#define BUTTON_DRIVER_TWO_ELECTROMAGNET_THROW 11
//#define BUTTON_DRIVER_TWO_ELECTROMAGNET_TEST 6
#define BUTTON_DRIVER_TWO_DISABLE 1
#define BUTTON_DRIVER_TWO_RETRACT 2
#define BUTTON_DRIVER_TWO_RESET 3

/*
 * Test Joystick Buttons
 */
#define BUTTON_TEST_DRIVE_FORWARD_3FT	1
#define BUTTON_TEST_DRIVE_BACK_3FT		2
#define BUTTON_TEST_TURN_90_PID			3
#define BUTTON_TEST_TURN_NEG_90_PID		4
#define BUTTON_TEST_TURN_90				7
#define BUTTON_TEST_TURN_NEG_90			8
#define BUTTON_TEST_MOVE_FORWARD_TIME	9
#define BUTTON_TEST_SOFT_THROW			10
#define BUTTON_TEST_SOFTER_THROW			11

/*
 * Test2 Joystick 
 */

#define BUTTON_TEST2_TILT_UP					1
#define BUTTON_TEST2_TILT_DOWN					2
#define BUTTON_TEST2_OPEN_GRABBER				3

#define BUTTON_TEST2_CLOSE_GRABBER				4
#define BUTTON_TEST2_ENTER_START_CONFIG			5
#define BUTTON_TEST2_EXIT_START_CONFIG			6
#define BUTTON_TEST2_THROW						7
#define BUTTON_TEST2_RETRACT					8
#define BUTTON_TEST2_THROW_RETRACT				9
#define BUTTON_TEST2_MOVE_STRAIGHT_3FT			10
#define BUTTON_TEST2_MOVE_STRAIGHT_5FT			11
#define BUTTON_TEST2_MOVE_BACKWARDS_3FT			12

/*
 * PWM
 */
#define DRIVE_RIGHT_FRONT_MOTOR	1
#define DRIVE_RIGHT_BACK_MOTOR	2
#define DRIVE_LEFT_FRONT_MOTOR	3
#define DRIVE_LEFT_BACK_MOTOR	4
#define INTAKE_TILT_MOTOR		5

/*
 * IO
 */
#define PRESSURE_SWITCH_CHANNEL		1
#define THROWER_LOW_LIMIT_SWITCH	2
#define INTAKE_LOW_LIMIT_SWITCH		3
#define INTAKE_HIGH_LIMIT_SWITCH	4
#define INTAKE_BALL_SENSOR 			5
#define INTAKE_OPEN_LIMIT_SWICH		6
#define DRIVE_ENCODER_LEFT_A		7//2
#define DRIVE_ENCODER_LEFT_B		8//3
#define DRIVE_ENCODER_RIGHT_A		9//4
#define DRIVE_ENCODER_RIGHT_B		10//5
#define THROWER_HIGH_LIMIT_SWITCH	11//7

#define INTAKE_STANDBY_LIMIT_SWITCH	12//10
#define INTAKE_BALL_SENSOR_TWO		14

/*
 * Relays
 */
#define COMPRESSOR_RELAY_CHANNEL 2
#define THROWER_ELECTROMAGNET_RELAY_CHANNEL 7
			    

/*
 * Solenoids 24v
 */
#define SOLENOID_MODULE				1
#define THROWER_SOLENOID_LEFT_IN	1
#define THROWER_SOLENOID_LEFT_OUT	2
#define THROWER_SOLENOID_RIGHT_IN	3
#define THROWER_SOLENOID_RIGHT_OUT	4
#define INTAKE_SOLENOID_IN			5
#define INTAKE_SOLENOID_OUT			6
#define INTAKE_SOLENOID_TILT_IN		7
#define INTAKE_SOLENOID_TILT_OUT	8


/*
 * Analog
 */

#define GYRO_HORIZONTAL 		1
#define THROWER_RANGE_FINDER 	2

/*
 * LEDs 12v
 */
#define LED_GREEN_RING 				1
#define LED_MODULE 					2
#define LED_RED_STRIP 				3
#define LED_BLUE_STRIP 				4
#define INTAKE_BALL_SENSOR_POWER	5
#define INTAKE_BALL_SENSOR_TWO_POWER 7


#endif
