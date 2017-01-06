package com.kennedyrobotics.commands;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class LowerCamera extends Command {

    public LowerCamera() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.cameraSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.cameraSubsystem.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.cameraSubsystem.lowerCamera();
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.cameraSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.cameraSubsystem.stop();
    }
}
