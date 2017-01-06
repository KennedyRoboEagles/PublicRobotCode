package com.kennedyrobotics.commands.drive;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveUntilCollisionCommand extends Command {

	private static final double SPEED = 0.5;
	private static final double TIME_OUT = 7;
	

	private final Timer timer = new Timer();
	private boolean finished = false;
	
    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	System.out.println("[DriveUntilCollision] Initiailizing");
    	Robot.chassis.stop();
    	timer.reset();
    	timer.start();
    }


	// Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double time = timer.get();
    	finished = Robot.sensorSubsystem.atWall() || time >= TIME_OUT;
        	
    	System.out.printf("Time %f\n", time);
    	
    	Robot.chassis.arcadeDrive(SPEED, 0);
	}

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
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
