package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveDistanceCommand extends Command {
	
	private static final double CLOSE_DISTANCE = 12;//INCHES
	
	private static final double TOLLERANCE = 1;
	
	private static final double SPEED = 0.5;
	private static final double MIN_SPEED = 0.1;
	
	private static final double YAW_P_GAIN = 0.001;
	private static final double DELTA_P_GAIN = 0.05;
	
	private final double distance;

	private double delta;
	
	/**
	 * NOTE: In inches
	 * @param distance distance to travel
	 */
	public DriveDistanceCommand(double distance) {
    	requires(Robot.chassis);
    	this.distance = distance;
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
    	double moveSpeed = SPEED;
    	
    	if(this.closeToGoalDistance()) {
    		moveSpeed = Math.max(moveSpeed * Math.abs(delta) * DELTA_P_GAIN, MIN_SPEED);
    	}

    	if(delta < 0) {
    		moveSpeed = -moveSpeed;
    	}
    	
    	double rotate = this.getYaw() * YAW_P_GAIN;
    	
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
    
    private double getYaw() {
    	return Robot.sensorSubsystem.getYaw();
    }
    
    private boolean closeToGoalDistance() {
    	return Math.abs(delta) <= CLOSE_DISTANCE;
    }
}
