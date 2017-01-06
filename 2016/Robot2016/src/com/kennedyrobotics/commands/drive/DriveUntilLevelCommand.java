package com.kennedyrobotics.commands.drive;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class DriveUntilLevelCommand extends Command {
	
	private final double speed;
	private final double timeout;

	private final Timer timer = new Timer();
	private boolean finished = false;

    public DriveUntilLevelCommand(double speed, double timeout) {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.chassis);
    	this.speed = speed;
    	this.timeout = timeout;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	System.out.println("[DriveUntilLevel] Initiailizing");
    	Robot.chassis.stop();
    	timer.reset();
    	timer.start();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double time = timer.get();
    	finished = Robot.sensorSubsystem.isLevel() || time >= timeout;
        	
    	System.out.printf("Time %f\n", time);
    	
    	Robot.chassis.arcadeDrive(speed, 0);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[DriveUntilLevel] Is Level, is stopping");
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[DriveUntilLevel] Interuppted, Stopping");
    	Robot.chassis.stop();
    }
}
