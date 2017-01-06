package com.kennedyrobotics.commands.shooter;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 * NOTE: use while held with this command.
 */
public class AimShooterUpCommand extends Command {

    public AimShooterUpCommand() {
       requires(Robot.shooterAimSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
		Robot.shooterAimSubsystem.up();
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Robot.shooterAimSubsystem.highLimit();
    }

    // Called once after isFinished returns true
    protected void end() {
    	//Robot.shooterAimSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	//Robot.shooterAimSubsystem.stop();
    }
}
