package com.kennedyrobotics.robot2016.subsystems;

import com.kennedyrobotics.robot2016.RobotMap;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ArmSubsystem extends Subsystem {
	
	public static final double EXTEND_SPEED = 0.5;
    public static final double RETRACT_SPEED = -0.5;
	
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final SpeedController extendMotor = new Jaguar(RobotMap.ARM_EXTEND_SPEED_CONTROLLER);
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public void extendArm() {
    	extendMotor.set(EXTEND_SPEED);
    }
    
    public void retractArm() {
    	extendMotor.set(RETRACT_SPEED);
    }
    
    public void stopArm() {
    	extendMotor.set(0.0);
    }
}

