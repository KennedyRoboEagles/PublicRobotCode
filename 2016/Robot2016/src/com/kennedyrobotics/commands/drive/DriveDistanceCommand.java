package com.kennedyrobotics.commands.drive;


import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveDistanceCommand extends Command {
	
	private static final double CLOSE_DISTANCE = 12;//INCHES
	
	private static final double TOLLERANCE = 1;
	
	private static final double SPEED = 0.8;
	private static final double MIN_SPEED = 0.6;
	
	private static final double YAW_P_GAIN = 0.000;
	private static final double DELTA_P_GAIN = 0.05;
	
	protected double distance;
	private final double speed;
	private final double lowSpeed;

	private double delta;
	
	/**
	 * NOTE: In inches
	 * @param distance distance to travel
	 */
	public DriveDistanceCommand(double distance) {
		this(distance, SPEED);
    }

	public DriveDistanceCommand(double distance, double speed, double lowSpeed) {
    	requires(Robot.chassis);
    	this.distance = -distance;
		this.speed = speed;
		this.lowSpeed = lowSpeed;
		
	}
	
	public DriveDistanceCommand(double distance, double speed) {
		this(distance, speed, MIN_SPEED);
	}

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("[DriveDistance] Initiailizing, Distance to travel " +  distance);
    	Robot.chassis.stop();
    	Robot.sensorSubsystem.getNavX().reset();
    	Robot.sensorSubsystem.getChassisLeftEncoder().reset();
    	Robot.sensorSubsystem.getChassisRightEncoder().reset();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	delta = distance - this.getEncoderDistnace();
    	double moveSpeed = speed;
    	
    	if(this.closeToGoalDistance()) {
    		moveSpeed = Math.max(moveSpeed * Math.abs(delta) * DELTA_P_GAIN, lowSpeed);
    	}

    	if(delta < 0) {
    		moveSpeed = -moveSpeed;
    	}
    	
    	double rotate = 0.0;
    	
    	System.out.println(
    			"[DriveDistance] Dist:" + distance + ", delta:" + delta + 
    			", moveSpeed:" + moveSpeed + ", rotate:" + rotate);
    	
    	
    	Robot.chassis.arcadeDrive(moveSpeed, rotate);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Math.abs(delta) < TOLLERANCE;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[DriveDistance] Reached target distance, Stopping chassis");
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[DriveDistance] Interuppted Stopping");
    	Robot.chassis.stop();
    }
    
    private double getEncoderDistnace() {
    	return Robot.sensorSubsystem.getChassisLeftEncoder().getDistance();
    }
    
    
    private boolean closeToGoalDistance() {
    	return Math.abs(delta) <= CLOSE_DISTANCE;
    }
}
