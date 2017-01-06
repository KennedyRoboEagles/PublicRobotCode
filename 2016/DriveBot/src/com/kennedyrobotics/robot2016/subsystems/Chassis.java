package com.kennedyrobotics.robot2016.subsystems;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.RobotDrive.MotorType;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

import static com.kennedyrobotics.robot2016.RobotMap.*;

import com.kennedyrobotics.robot2016.Robot;
import com.kennedyrobotics.robot2016.commands.DriveWithJoystick;

/**
 *
 */
public class Chassis extends Subsystem {
    
	public static final double MAX_SPEED = 100;//Inches per second 
	
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
    	frontLeft = new Jaguar(CHASSIS_JAGUAR_FRONT_LEFT);
    	frontRight = new Jaguar(CHASSIS_JAGUAR_FRONT_RIGHT);
    	backLeft = new Jaguar(CHASSIS_JAGUAR_BACK_LEFT);
    	backRight = new Jaguar(CHASSIS_JAGUAR_BACK_RIGHT);
    	
    	drive = new RobotDrive(frontLeft, backLeft, frontRight, backRight);

    	drive.setInvertedMotor(MotorType.kFrontLeft, false);
    	drive.setInvertedMotor(MotorType.kFrontRight, false);
    	drive.setInvertedMotor(MotorType.kRearLeft, false);
    	drive.setInvertedMotor(MotorType.kRearRight, false);
    	
    	drive.setSafetyEnabled(false);
    }
    
    public void arcadeDrive(Joystick stick) {
    	double x = stick.getX();
    	double y = stick.getY();
    	
    	x = -x;
    	
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
    	backLeft.set(speed);
    }
    
    public void setRight(double speed) {
    	frontRight.set(speed);
    	backRight.set(speed);
    }
    
    public void stop() {
    	drive.tankDrive(0.0, 0.0);
    }

    public Encoder getLeftEncoder() {
    	return Robot.sensorSubsystem.getChassisLeftEncoder();
    }
    
    public Encoder getRightEncoder() {
    	return Robot.sensorSubsystem.getChassisRightEncoder();
    }
    
}

