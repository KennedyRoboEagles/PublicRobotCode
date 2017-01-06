package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveUntilCollisionCommand extends Command {

	private static final double SPEED = 0.5;
	

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("[DriveUntilCollision] Initiailizing");
    	Robot.chassis.stop();
    }


	// Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(Robot.sensorSubsystem.getCollision()) {
    		Robot.chassis.stop();
    	} else {
    		Robot.chassis.arcadeDrive(SPEED, 0.0);
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Robot.sensorSubsystem.getCollision();
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[DriveUntilCollision] Have collided, is stopping");
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[DriveUntilCollision] Interuppted, Stopping");
    	Robot.chassis.stop();
    }
}
