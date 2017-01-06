package com.kennedyrobotics.commands.shooter;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 * This command fires the shooter at the low goal.
 */
public class ShootLowCommand extends Command {

	private Timer timer;
	private final double TIME_TO_RUN = 0.5;
	
    public ShootLowCommand() {
    	requires(Robot.shooterSubsystem);
    	this.timer = new Timer();
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.shooterSubsystem.shootBallLow();
    	timer.reset();
    	timer.start();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
    	return timer.get() > TIME_TO_RUN;
    }

    // Called once after isFinished returns true
    protected void end() {
    	timer.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
