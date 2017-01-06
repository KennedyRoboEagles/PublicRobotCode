package com.kennedyrobotics.commands.vision;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class VisionTurnToTarget extends Command {

	private boolean finished;
	
    public VisionTurnToTarget() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	boolean newFrame = Math.abs(Robot.visionSubsystem.getTask().getLastProcessTimeStamp() - Timer.getFPGATimestamp()) < 0.1;
    	if(newFrame) {
    		System.out.println("New Frame");
    		double comX = Robot.visionSubsystem.getTask().getTargetcomX();
    		double delta = 640/2 - comX;
    		if(delta < -15) {
    			Robot.chassis.arcadeDrive(0, -0.67);
    		} else if(15 < delta) {
    			Robot.chassis.arcadeDrive(0, 0.67);
    		} else {
    			finished = true;
    		}
    	} else {
    		System.out.println("Waiting for new frame");
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
