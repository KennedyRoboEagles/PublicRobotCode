package com.kennedyrobotics.robot2016.subsystems;

import com.kennedyrobotics.robot2016.Robot;
import com.kennedyrobotics.robot2016.RobotMap;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ShooterTiltSubsystem extends Subsystem {
	
	public static final double RAISE_SPEED = 0.5;
	public static final double LOWER_SPEED = -0.5;
	
	private final SpeedController shooterAimMotor = new Jaguar(RobotMap.BALL_SHOOTER_TILT_SPEED_CONTROLLER);
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public boolean isAtLowLimit(){
    	return Robot.sensorSubsystem.getShooterAimTiltLowLimit();
    }
    
    public boolean isAtHighLimit(){
    	return Robot.sensorSubsystem.getShooterAimTiltHighLimit();
    }
    
    public void raiseShooter(){
    	shooterAimMotor.set(RAISE_SPEED);
    }
    
    public void lowerShooter(){
    	shooterAimMotor.set(LOWER_SPEED);
    }
    
    public void stopShooter(){
    	shooterAimMotor.set(0.0);
    }
}

