package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class RaiseShooterCommand extends Command {

    public RaiseShooterCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.shooterTiltSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.shooterTiltSubsystem.stopShooter();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.shooterTiltSubsystem.raiseShooter();
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.shooterTiltSubsystem.stopShooter();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.shooterTiltSubsystem.stopShooter();
    }
}
