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
	
	/**
	 * PWM 
	 */
	
	public static final int CHASSIS_JAGUAR_FRONT_LEFT = 0;
//	public static final int CHASSIS_JAGUAR_BACK_LEFT = 1;
	public static final int CHASSIS_JAGUAR_FRONT_RIGHT = 1;
//	public static final int CHASSIS_JAGUAR_BACK_RIGHT = 3;
	
	public static final int ARM_TILT_SPEED_CONTROLLER  = 4;
	public static final int ARM_EXTEND_SPEED_CONTROLLER = 5;
	
	/**
	 * DIO
	 */
	
	public static final int CHASSIS_WALL_DEDECTOR  = 1;
	public static final int CHASSIS_ENCODER_LEFT_A = 10;
	public static final int CHASSIS_ENCODER_LEFT_B = 11;
	public static final int CHASSIS_ENCODER_RIGHT_A = 12;
	public static final int CHASSIS_ENCODER_RIGHT_B = 13;

	public static final int ARM_TILT_HIGH_LIMIT = 4;
	public static final int ARM_TILT_LOW_LIMIT = 5;
	
	/**
	 * PCM
	 */
	public static final int ARM_SOLENOID_FORWARD = 0;
	public static final int ARM_SOLENOID_REVERSE = 1;

}
