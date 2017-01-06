package com.kennedyrobotics.commands.drive;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class TurnSpecifiedDegreesCommand extends Command {

	private static final double DEGREES_PRECISION = 3;
	private final Timer timer = new Timer();
	
	private boolean finished = false;
	private double goalAngle = 0.0;
	private final double degreesToTurn;
	
    public TurnSpecifiedDegreesCommand(double degreesToTurn) {
    	if(Math.abs(degreesToTurn) > 180) {
    		throw new IllegalArgumentException("Degrees not in range +-180");
    	}
    	requires(Robot.chassis);
    	this.degreesToTurn = degreesToTurn;
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	
    	Robot.sensorSubsystem.getNavX().zeroYaw();
    	System.out.println(Robot.sensorSubsystem.getYaw());
    	goalAngle = degreesToTurn;
    	
    	timer.reset();
    	timer.start();
    	
    	System.out.println("[TurnSpecifiedDegreesCommand] Going to turn " + degreesToTurn);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(!timer.hasPeriodPassed(0.2)) {
    		return;
    	}
    	
    	double currentAngle = Robot.sensorSubsystem.getYaw();
    	double angleDifference = goalAngle - currentAngle;
    	//angleDifference %= 180;
    	System.out.println("Angle Difference " + angleDifference + " gaolAngle " + goalAngle + " currentAngle " + currentAngle);
    	
    	double turnRate = 0;
    	if(Math.abs(angleDifference) <  DEGREES_PRECISION) {
        	Robot.chassis.stop();
    		finished = true;
    		return;
    	} else {
    		if(Math.abs(angleDifference) > 20) {
    			turnRate = 0.9;
    		} if(Math.abs(angleDifference) > 10) {
    			turnRate = 0.8;
    		} else { 
    		
    			turnRate = 0.7;
    		}
    	}
    	
    	if(angleDifference > 0) {
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
    	timer.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[TurnSpecifiedDegreesCommand] Interrupted.");
    	Robot.chassis.stop();
    	timer.stop();
    }
}
