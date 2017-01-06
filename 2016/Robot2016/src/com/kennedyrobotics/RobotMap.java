package com.kennedyrobotics;
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
	public static final int OI_JOYSTICK_SHOOTER = 1;
	public static final int OI_JOYSTICK_TEST = 3;

	
	/**
	 * Driver Buttons
	 */
	public static final int OI_DRIVER_SWAP = XboxPcJoystickMapping.A;//A

	/**
	 * Shooter Buttons
	 */
	
	public static final int OI_SHOOTER_PICKUP_BALL = XboxPcJoystickMapping.A;
	public static final int OI_SHOOTER_SHOOT_LOW_GOAL = XboxPcJoystickMapping.LeftBumper;

	//According to Steve, we won't have much else besides
	//launch ball button, the three auto-breach buttons,
	//and camera toggles. We'll see how that goes.
	
	/**
	 * PWM 
	 */
	
	public static final int CHASSIS_JAGUAR_FRONT_LEFT = 2;
	public static final int CHASSIS_JAGUAR_BACK_LEFT = 3;
	public static final int CHASSIS_JAGUAR_FRONT_RIGHT = 0;
	public static final int CHASSIS_JAGUAR_BACK_RIGHT = 1;
	public static final int BALL_SHOOTER_LEFT_SPEED_CONTROLLER = 4;
	public static final int BALL_SHOOTER_RIGHT_SPEED_CONTROLLER = 5;
	public static final int ARM_EXTEND_SPEED_CONTROLLER = 6;
	public static final int CAMERA_TILT_MOTOR = 7;

	/**
	 * CANID
	 */
	public static final int ARM_TILT_CAN_SPEED_CONTROLLER  = 1;
	
	/**
	 * DIO
	 */
	public static final int CHASSIS_ENCODER_LEFT_A = 0;
	public static final int CHASSIS_ENCODER_LEFT_B = 1;
	
	public static final int CHASSIS_ENCODER_RIGHT_A = 2;
	public static final int CHASSIS_ENCODER_RIGHT_B = 3;
	
	public static final int SHOOTER_TILT_LOW_LIMIT = 4;
	public static final int SHOOTER_TILT_HIGH_LIMIT = 5;
	
	public static final int ARM_HIGH_LIMIT = 6;
	public static final int ARM_LOW_LIMIT = 7;
//	public static final int LED = 6;
	public static final int LINE_DEDECTOR = 8;
	public static final int ARM_PRESENT_LIMIT = 9;
	
	public static final int BALL_SHOOTER_TILT_ENCODER_A = 10;
	public static final int BALL_SHOOTER_TILT_ENCODER_B = 11;

//	public static final int ARM_EXTEND_ENCODER_A = 4;
//	public static final int ARM_EXTEND_ENCODER_B = 5;
	
//	public static final int ARM_EXTEND_LIMIT = 10;
//	public static final int ARM_RETRACT_LIMIT = 11;
	
//	public static final int ARM_TILT_HIGH_LIMIT = 14;
//	public static final int ARM_TILT_LOW_LIMIT = 15;
	
//	public static final int ARM_TILT_ENCODER_A = 16;
//	public static final int ARM_TILT_ENCODER_B = 17;
	
	public static final int CHASSIS_WALL_DETECTOR = 19;


	/**
	 * PCM
	 */
	public static final int KICKER_SOLENOID_FORWARD = 0;
	public static final int KICKER_SOLENOID_REVERSE = 1;
	public static final int SHOOTER_AIM_FORWARD = 2;
	public static final int SHOOTER_AIM_BACKWARD = 3;
	public static final int ARM_FORWARD = 4;
	public static final int ARM_BACKWARD = 5;
	
	/**
	 * Relay
	 */
	public static final int ELECTROMAGNET_RELAY = 0;
	
	
}
