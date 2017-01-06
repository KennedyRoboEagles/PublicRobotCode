package com.kennedyrobotics.commands.shooter;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class ShooterSupervisorCommand extends Command {

	public enum State {
		kIdle,
		kShooting,
		kInjesting
	}
	
	public static final double START_SHOOTING_ANGLE = 30;
	public static final double END_SHOOTING_ANGLE = 80;
	
    public ShooterSupervisorCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.shooterSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	this.setState(State.kIdle);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	
    	double shooterAngle = Robot.shooterAimSubsystem.getCurrentTiltAngle();
    	
    	/*
    	 * So the shooter will injest the wall when it is at the low limit
    	 * The shooter will be shooting when it is tilted between the start and end angles.
    	 * All other times the shooter will be off or idling.
    	 */
    	
    	if(Robot.shooterAimSubsystem.lowLimit()) {
    		this.setState(State.kInjesting);
    	} else if(START_SHOOTING_ANGLE <= shooterAngle && shooterAngle >= END_SHOOTING_ANGLE) {
    		this.setState(State.kShooting);
    	} else {
    		this.setState(State.kIdle);
    	}
    	
    	switch (this.getState()) {
		case kShooting:
			Robot.shooterSubsystem.shootBallLow();
		case kInjesting:
			Robot.shooterSubsystem.injestBall();
			break;
		case kIdle:
			Robot.shooterSubsystem.stop();
			break;
		default:
			this.setState(State.kIdle);
			Robot.shooterSubsystem.stop();
			break;
		}
    	
    	SmartDashboard.putString("Shooter State", this.getState().name());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
		Robot.shooterSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
		Robot.shooterSubsystem.stop();
    }
    
    private State getState() {
    	return Robot.shooterSubsystem.getState();
    }
    
    private void setState(State state) {
    	Robot.shooterSubsystem.setState(state);
    }
}
