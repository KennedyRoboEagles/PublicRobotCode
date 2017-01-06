package com.kennedyrobotics.commands;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveForwardFullBlastCommand extends Command {

    public DriveForwardFullBlastCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.chassis.stop();
    	Robot.sensorSubsystem.getNavX().reset();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double move = Robot.sensorSubsystem.getYaw() * 0.05;
    	Robot.chassis.arcadeDrive(-1.0, move);
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
