package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class ComrpressorSupervisorCommand extends Command {

    public ComrpressorSupervisorCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.compressorSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("Starting compressor");
    	Robot.compressorSubsystem.start();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("Stopping compressor");
    	Robot.compressorSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("Stopping compressor");
    	Robot.compressorSubsystem.stop();
    }
}
