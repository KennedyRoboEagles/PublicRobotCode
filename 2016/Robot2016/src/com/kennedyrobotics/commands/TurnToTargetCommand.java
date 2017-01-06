package com.kennedyrobotics.commands;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class TurnToTargetCommand extends Command {

	public static final double TOLLERANCE = 20;
	
    public TurnToTargetCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.chassis.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double rotate = 0;
    	if(Robot.visionSubsystem.getTask().isTargetPresent()) {
	    	double delta = 480/2 - Robot.visionSubsystem.getTask().getTargetcomX();
	    	if(TOLLERANCE < delta) {
	    		rotate = 0.7;
	    	} else if(delta < -TOLLERANCE){
	    		rotate = -0.7;
	    	} else {
	    		rotate = 0;
	    	}
	    	SmartDashboard.putNumber("COMX Delta", delta);
    	} else {
	    	SmartDashboard.putNumber("COMX Delta", 0);
    	}
    	
    	System.out.println(rotate);
    	Robot.chassis.arcadeDrive(0.0, rotate);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.chassis.stop();
    }
}
