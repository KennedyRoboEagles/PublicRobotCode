package com.kennedyrobotics.robot2016.subsystems;

import com.kennedyrobotics.robot2016.Robot;
import com.kennedyrobotics.robot2016.RobotMap;

import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ArmTiltSubsystem extends Subsystem {
	public static final double RAISE_SPEED = -0.75;
	public static final double LOWER_SPEED = 0.750;
    // Put methods for controlling this subsystem
    // here. Call these from Commands.
	
	private final SpeedController aimMotor = new Talon(RobotMap.ARM_TILT_SPEED_CONTROLLER);
	
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public boolean isAtLowLimt() {
    	return Robot.sensorSubsystem.getArmAimTiltLowLimit();
    }
    
    
    public boolean isAtHighLimit() {
    	return Robot.sensorSubsystem.getArmAimTiltHighLimit();
    }
    
    public void raiseArm() {
    	aimMotor.set(RAISE_SPEED);
    }
    
    public void lowerArm() {
    	aimMotor.set(LOWER_SPEED);
    }
    
    public void stopArm() {
    	aimMotor.set(0);
    }
 }

