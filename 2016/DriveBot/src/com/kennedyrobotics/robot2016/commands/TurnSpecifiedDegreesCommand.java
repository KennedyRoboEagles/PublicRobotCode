package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class TurnSpecifiedDegreesCommand extends Command {

	private static final double DEGREES_PRECISION = 2;
	
	private boolean finished = false;
	private double startingAngle = 0.0;
	private double goalAngle = 0.0;
	private final double degreesToTurn;
	
    public TurnSpecifiedDegreesCommand(double degreesToTurn) {
    	requires(Robot.chassis);
    	this.degreesToTurn = degreesToTurn;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	startingAngle = Robot.sensorSubsystem.getYaw();
    	goalAngle = startingAngle + degreesToTurn;
    	
    	System.out.println("[TurnSpecifiedDegreesCommand] Going to turn " + degreesToTurn);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	
    	double currentAngle = Robot.sensorSubsystem.getYaw();
    	double angleDifference = goalAngle - currentAngle;
    	
    	System.out.println("Angle Difference " + angleDifference + " gaolAngle " + goalAngle + " currentAngle " + currentAngle);
    	
    	double turnRate = 0;
    	if(Math.abs(angleDifference) <  DEGREES_PRECISION) {
    		Robot.chassis.stop();
    		finished = true;
    	} else {
    		if(Math.abs(angleDifference) < 10) {
    			turnRate = 0.5;
    		} else { 
    			turnRate = 0.3;
    		}
    	}
    	
    	if(angleDifference < 0) {
    		turnRate = -turnRate;
    	}
    	
    	Robot.chassis.arcadeDrive(0.0, turnRate);
    	
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[TurnSpecifiedDegreesCommand] completed.");
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[TurnSpecifiedDegreesCommand] Interrupted.");
    	Robot.chassis.stop();
    }
}
