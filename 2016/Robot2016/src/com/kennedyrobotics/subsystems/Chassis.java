package com.kennedyrobotics.subsystems;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;

import static com.kennedyrobotics.RobotMap.*;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.commands.drive.DriveWithJoystick;

/**
 *
 */
public class Chassis extends Subsystem {
    
	public static final double MAX_SPEED = 12 * 20;//Inches per second 
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final SpeedController frontLeft;
	private final SpeedController frontRight;
	private final SpeedController backLeft;
	private final SpeedController backRight;
	
	private final RobotDrive drive;
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	setDefaultCommand(new DriveWithJoystick());
    }
    
    public Chassis() {
    	frontLeft = new Talon(CHASSIS_JAGUAR_FRONT_LEFT);
    	frontRight = new Talon(CHASSIS_JAGUAR_FRONT_RIGHT);
    	backLeft = new Talon(CHASSIS_JAGUAR_BACK_LEFT);
    	backRight = new Talon(CHASSIS_JAGUAR_BACK_RIGHT);
     	
    	drive = new RobotDrive(frontLeft, backLeft, frontRight,backRight);

    	drive.setSafetyEnabled(false);
    }
    
    public Encoder getLeftEncoder() {
    	return Robot.sensorSubsystem.getChassisLeftEncoder();
    }
    
    public Encoder getRightEncoder() {
    	return Robot.sensorSubsystem.getChassisRightEncoder();
    }
    
    
    public void arcadeDrive(Joystick stick) {
    	double x = stick.getX();
    	double y = stick.getY();
    	
    	y = -y;
    	
    	drive.arcadeDrive(y,x);
    }
    
    public void arcadeDrive(double move, double rotate) {
    	drive.arcadeDrive(move, rotate);
    }
    
    public void tankDrive(double left, double right) {
    	drive.tankDrive(left, right);
    }
    
    public void setLeft(double speed) {
    	frontLeft.set(speed);
    }
    
    public void setRight(double speed) {
    	frontRight.set(speed);
    }
    
    public void stop() {
    	drive.tankDrive(0.0, 0.0);
    }  
}