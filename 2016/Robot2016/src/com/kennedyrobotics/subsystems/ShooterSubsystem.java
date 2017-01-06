package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.RobotMap;
import com.kennedyrobotics.commands.shooter.ShooterOffCommand;
import com.kennedyrobotics.commands.shooter.ShooterSupervisorCommand.State;

import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class ShooterSubsystem extends Subsystem {
    
	public static final double SHOOT_LOW_LEFT_SPEED = -0.75;
	public static final double SHOOT_LOW_RIGHT_SPEED = 0.75;
	
	// High settings uncalibrated
	public static final double SHOOT_HIGH_LEFT_SPEED = -0.75;
	public static final double SHOOT_HIGH_RIGHT_SPEED = 0.75;
	
	public static final double INJEST_LEFT_SPEED = 0.5;
	public static final double INJEST_RIGHT_SPEED = -0.5;
	
	private final SpeedController left = new Talon(RobotMap.BALL_SHOOTER_LEFT_SPEED_CONTROLLER);
	private final SpeedController right = new Talon(RobotMap.BALL_SHOOTER_RIGHT_SPEED_CONTROLLER);
	
	private State state;
	public void setState(State state) {
		this.state = state;
	}
	
	public State getState() {
		return this.state;
	}
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	//setDefaultCommand(new ShooterSafeCommandGroup());
    	setDefaultCommand(new ShooterOffCommand());
    }
    
    public void set(double leftspeed, double rightspeed) {
    	left.set(leftspeed);
    	right.set(rightspeed);
    	SmartDashboard.putNumber("Shooter Speed left", leftspeed);
    	SmartDashboard.putNumber("Shooter Speed right", rightspeed);

    }
    
    public void stop() {
    	this.set(0.0, 0.0);
    }
    
    public void shootBallLow() {
    	this.set(SHOOT_LOW_LEFT_SPEED, SHOOT_LOW_RIGHT_SPEED);
    }
    
    public void shootBallHigh() {
    	this.set(SHOOT_HIGH_LEFT_SPEED, SHOOT_HIGH_RIGHT_SPEED);
    }
    
    public void injestBall() {
    	this.set(INJEST_LEFT_SPEED, INJEST_RIGHT_SPEED);
    }
}

