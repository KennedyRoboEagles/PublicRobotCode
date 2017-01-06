package org.usfirst.frc.team3081.robot.commands;

import org.usfirst.frc.team3081.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class SetShooterAimSpeedCommand extends Command {

	private double speed;
	
	public SetShooterAimSpeedCommand(double speed) {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
		this.speed=speed;
    	requires(Robot.shooterAimSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.shooterAimSubsystem.stop();;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.shooterAimSubsystem.set(speed);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {    	
    	Robot.shooterAimSubsystem.stop();;

    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {    	
    	Robot.shooterAimSubsystem.stop();;

    }
}
