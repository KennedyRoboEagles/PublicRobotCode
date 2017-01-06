package com.kennedyrobotics.robot2016.commands;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.PIDSourceType;
import edu.wpi.first.wpilibj.command.Command;

import static com.kennedyrobotics.robot2016.Robot.chassis;

import com.kennedyrobotics.robot2016.subsystems.Chassis;

/**
 * Will chain the rate the rate of the left encoder to speed of the right encoder
 */
public class PIDDriveDistanceCommand extends Command {
	
	/**
	 * Helper class to drive the right side of the chassis with a PID controller
	 * @author Ryan
	 *
	 */
	private class RightPIDHelper implements PIDSource, PIDOutput {
	    @Override 
	    public double pidGet() {
	    	return chassis.getRightEncoder().getRate(); 
	    }
	    @Override public PIDSourceType getPIDSourceType() { return PIDSourceType.kRate; }
	    @Override public void setPIDSourceType(PIDSourceType pidSource) {}
	    @Override public void pidWrite(double output) { chassis.setRight(output); }
	}
	
	public static final double TOLLERANCE = 1;//Inches
	
	private final PIDController rightController;
	private final double distance;
	private final double speed;
	
	private boolean finished = false;
	
	/**
	 * Can set the direction and speed that the robot will travel in.
	 * @param distance In inches
	 * @param speed Speed to travel at, please only 0->1.0
	 */
    public PIDDriveDistanceCommand(double distance, double speed) {
    	requires(chassis);
    	
    	this.distance = distance;
    	this.speed = Math.abs(speed);
    	
    	RightPIDHelper rightPIDHelper = new RightPIDHelper();
    	rightController = new PIDController(0.0, 0.0, 0.0, rightPIDHelper, rightPIDHelper);
    	//TODO:Set PID options
    	rightController.setInputRange(-Chassis.MAX_SPEED, Chassis.MAX_SPEED);
    	rightController.setOutputRange(-1.0, 1.0);
    	rightController.setAbsoluteTolerance(1);
    }
    
    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	
    	chassis.getLeftEncoder().reset();
    	chassis.getRightEncoder().reset();
    	
    	rightController.reset();
    	rightController.setSetpoint(0.0);
    	rightController.enable();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	//Chain the right wheels rate to the left wheels rate
    	rightController.setSetpoint(chassis.getLeftEncoder().getRate());
    	
    	double delta = chassis.getLeftEncoder().getDistance() - distance;
    	
    	if(Math.abs(delta) < TOLLERANCE) {
    		finished = true;
    		return;
    	}
    	
    	double speed = this.speed;
    	
    	if(Math.abs(distance) < 0) {
    		speed *= -1;
    	}
    	
    	chassis.setLeft(speed);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
    	this.cleanUp();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	this.cleanUp();
    }
    
    
    private void cleanUp() {
    	rightController.disable();
    	chassis.stop();
    }
}
