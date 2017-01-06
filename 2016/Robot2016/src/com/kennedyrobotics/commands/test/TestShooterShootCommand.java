package com.kennedyrobotics.commands.test;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 * Not this command does not exit
 */
public class TestShooterShootCommand extends Command {
	
	private final double SHOOTER_SPIN_UP_TIME = 1;
	private final double SHOOTER_KICK_TIME = SHOOTER_SPIN_UP_TIME + 0.5;
	
	private Timer timer;

    public TestShooterShootCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.shooterSubsystem);
    	timer = new Timer();
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	timer.reset();
    	timer.start();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.shooterSubsystem.shootBallLow();
    	if (timer.get() > SHOOTER_SPIN_UP_TIME)
    	{
    		Robot.kickerSubsystem.extend();
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return timer.get() > SHOOTER_KICK_TIME;
    }
    
    private void cleanup() {
    	Robot.shooterSubsystem.stop();
    	timer.stop();
    	Robot.kickerSubsystem.retract();
    }

    // Called once after isFinished returns true
    protected void end() {
    	cleanup();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	cleanup();
    }
}
