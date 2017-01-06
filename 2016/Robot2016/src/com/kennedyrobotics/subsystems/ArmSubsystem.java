package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.RobotMap;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ArmSubsystem extends Subsystem {
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final DoubleSolenoid solenoid = new DoubleSolenoid(RobotMap.ARM_EXTEND_SPEED_CONTROLLER, RobotMap.ARM_BACKWARD);
	
    public void initDefaultCommand() {
    }
    
    public void up() {
    	solenoid.set(DoubleSolenoid.Value.kForward);
    }
    
    public void down() {
    	solenoid.set(DoubleSolenoid.Value.kReverse);
    }
    
    public void stop() {
    	solenoid.set(DoubleSolenoid.Value.kOff);
    }
    
    public boolean lowLimit() {
    	return Robot.sensorSubsystem.getArmLowLimit();
    }
    
    public boolean highLimit() {
    	return Robot.sensorSubsystem.getArmHighLimit();
    	
    }
  }

