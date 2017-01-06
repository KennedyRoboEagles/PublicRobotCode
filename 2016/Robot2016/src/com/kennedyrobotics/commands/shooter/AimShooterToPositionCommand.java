package com.kennedyrobotics.commands.shooter;

import com.kennedyrobotics.Movement;
import com.kennedyrobotics.Robot;
import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class AimShooterToPositionCommand extends Command {

	private double value;
	private Movement movement;
	
	
	private boolean finished = false;
	
	
    public AimShooterToPositionCommand(Movement movement, double value) {
        this.value = value;
        this.movement = movement;
    }

    // Called just before this Command runs the first time
    protected void initialize() {

    	double setpoint;
    	
    	switch (movement) {
		case kAdjustment:
			setpoint = Robot.shooterAimSubsystem.getCurrentTiltAngle() + value;
			break;

		case kSetpoint:
			setpoint = value;
			break;
		default:
			throw new RuntimeException("Invalid movement");
		}
    	
    	Robot.shooterAimSubsystem.setDesiredTiltAngle(setpoint);
    	
    	finished = false;
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	finished = Robot.shooterAimSubsystem.getOnTarget() && !Robot.shooterAimSubsystem.inCalibration();
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {}

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {}
    
    
}
