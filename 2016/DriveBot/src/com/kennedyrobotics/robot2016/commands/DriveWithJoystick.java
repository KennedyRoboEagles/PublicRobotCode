package com.kennedyrobotics.robot2016.commands;

import edu.wpi.first.wpilibj.command.Command;

import static com.kennedyrobotics.robot2016.Robot.*;

/**
 *
 */
public class DriveWithJoystick extends Command {

    public DriveWithJoystick() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	chassis.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	chassis.arcadeDrive(oi.getDriverStick());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	chassis.stop();
    }
}
