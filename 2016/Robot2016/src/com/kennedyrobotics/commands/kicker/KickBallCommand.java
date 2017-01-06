package com.kennedyrobotics.commands.kicker;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class KickBallCommand extends Command {

	private boolean finished = false;
	
    public KickBallCommand() {}
    
    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	if(Robot.kickerSubsystem.isCalibrated()) {
        	Robot.kickerSubsystem.kickBall();
    	} else {
    		System.out.println("The kicker sybsystem is not calibrated not kicking");
    		finished = true;
    	}
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	finished = Robot.kickerSubsystem.isDone();
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
