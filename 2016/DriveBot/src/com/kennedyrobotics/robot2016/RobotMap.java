package com.kennedyrobotics.robot2016;
/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
    // For example to map the left and right motors, you could define the
    // following variables to use with your drivetrain subsystem.
    // public static int leftMotor = 1;
    // public static int rightMotor = 2;
    
    // If you are using multiple modules, make sure to define both the port
    // number and the module. For example you with a rangefinder:
    // public static int rangefinderPort = 1;
    // public static int rangefinderModule = 1;
	
	
	/**
	 * Joysticks
	 */
	public static final int OI_JOYSTICK_DRIVER = 0;
	
	/**
	 * Driver Buttons
	 */
	public static final int OI_DRIVER_LOWER_ARM = 1;
	public static final int OI_DRIVER_RAISE_ARM = 2;

	public static final int OI_DRIVER_RETRACT_ARM = 3;
	public static final int OI_DRIVER_EXTEND_ARM = 5;
	
	public static final int OI_DRIVER_RAISE_SHOOTER = 6;
	public static final int OI_DRIVER_LOWER_SHOOTER = 7;
	
	/**
	 * PWM 
	 */
	
	public static final int CHASSIS_JAGUAR_FRONT_LEFT = 0;
	public static final int CHASSIS_JAGUAR_FRONT_RIGHT = 1;
	public static final int CHASSIS_JAGUAR_BACK_LEFT = 2;
	public static final int CHASSIS_JAGUAR_BACK_RIGHT = 3;
	
	public static final int ARM_TILT_SPEED_CONTROLLER  = 4;
	public static final int ARM_EXTEND_SPEED_CONTROLLER = 5;
	public static final int BALL_SHOOTER_LEFT_SPEED_CONTROLLER = 6;
	public static final int BALL_SHOOTER_RIGHT_SPEED_CONTROLLER = 7;
	public static final int BALL_SHOOTER_TILT_SPEED_CONTROLLER = 9;
	
	/**
	 * DIO
	 */
	public static final int CHASSIS_ENCODER_LEFT_A = 0;
	public static final int CHASSIS_ENCODER_LEFT_B = 1;
	public static final int CHASSIS_ENCODER_RIGHT_A = 2;
	public static final int CHASSIS_ENCODER_RIGHT_B = 3;
	public static final int ARM_TILT_ENCODER_A = 4;
	public static final int ARM_TILT_ENCODER_B = 5;
	public static final int ARM_EXTEND_ENCODER_A = 6;
	public static final int ARM_EXTEND_ENCODER_B = 7;
	public static final int BALL_SHOOTER_TILT_ENCODER_A = 8;
	public static final int BALL_SHOOTER_TILT_ENCODER_B = 9;
	public static final int BALL_SHOOTER_LEFT_ENCODER_A = 10;
	public static final int BALL_SHOOTER_LEFT_ENCODER_B = 11;
	public static final int BALL_SHOOTER_RIGHT_ENCODER_A = 12;
	public static final int BALL_SHOOTER_RIGHT_ENCODER_B = 13;

	public static final int ARM_TILT_HIGH_LIMIT = 14;
	public static final int ARM_TILT_LOW_LIMIT = 15;
	public static final int ARM_RETRACT_LIMIT = 16;
	public static final int ARM_EXTEND_LIMIT = 17;
	public static final int BALL_SHOOTER_TILT_HIGH_LIMIT = 18;
	public static final int BALL_SHOOTER_TILT_LOW_LIMIT = 19;
	
	/**
	 * PCM
	 */
	public static final int ARM_SOLENOID_FORWARD = 0;
	public static final int ARM_SOLENOID_REVERSE = 1;
	
	/**
	 * Things we'll need on the physical robot include:
	 * 8 speed controllers (4 jaguars/ 2 ambiguous)(2 can be in the same port
	 * for the two ball shooter motors)
	 * 7 encoders
	 * 5 limit switches
	 * motors - ?
	 * the gyro navX thingy
	 * 
	 *...a camera?
	 * 
	 */

}
