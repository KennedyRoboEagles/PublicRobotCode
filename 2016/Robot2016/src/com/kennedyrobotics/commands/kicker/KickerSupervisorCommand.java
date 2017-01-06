package com.kennedyrobotics.commands.kicker;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import static com.kennedyrobotics.Robot.kickerSubsystem;

import com.kennedyrobotics.Robot;

/**
 * Might not need the retract limit, could just till the kicker to move back for a short 
 * period of time to have it retract fully.
 */
public class KickerSupervisorCommand extends Command {

	public enum State {
		kEnterCalibration,
		kCalibration,
		kIdle,
		kStartKick,
		kKicking,
		kPausing,
		kReturning,
		kStopped,
	}
	
	public static final double RETRACT_TIME = 0.25;
	public static final double KICK_TIME = 0.5;
	public static final double PAUSE_TIME = 0.1;
	
	private final Timer timer = new Timer();
		
    public KickerSupervisorCommand() {
    	requires(kickerSubsystem);
    }

    // Called just before this Command runs the first time
	protected void initialize() {
    	kickerSubsystem.setDone(false);
    	if(Robot.kickerSubsystem.isCalibrated()) {
    		this.setState(State.kIdle);
    	} else {
    		this.setState(State.kEnterCalibration);
    	}
    }

    // Called repeatedly when this Command is scheduled to run
	protected void execute() {
    	switch (this.getState()) {
		case kEnterCalibration:
			System.out.println("Starting Kicker calibration");
			timer.reset();
			timer.start();
			this.setState(State.kCalibration);
			break;
		case kCalibration:
			if(timer.hasPeriodPassed(RETRACT_TIME)) {
				timer.stop();
				Robot.kickerSubsystem.setCalibrated(true);
				this.setState(State.kIdle);
				System.out.println("Kicker is at retract limit, calibrated");
				break;
			}
			System.out.printf("Kicker Calibration time %f\n", timer.get());
			kickerSubsystem.retract();
			break;
		case kIdle:
			//To nothing
			kickerSubsystem.setDone(true);
			break;
		case kStartKick:
			System.out.println("Starting kick");
			kickerSubsystem.setDone(false);
			timer.reset();
			timer.start();
			this.setState(State.kKicking);
			break;
		case kKicking:
			kickerSubsystem.setDone(false);
			if(timer.hasPeriodPassed(KICK_TIME)) {
				this.setState(State.kPausing);
				timer.reset();
				timer.start();
				break;
			}
			System.out.printf("Kicking %f\n", timer.get());
			kickerSubsystem.extend();
			
			break;
		case kPausing:
			kickerSubsystem.setDone(false);
			if(timer.hasPeriodPassed(PAUSE_TIME)) {
				this.setState(State.kReturning);
				timer.stop();
				timer.start();
				break;
			}
			System.out.printf("Pausing %f\n", timer.get());
			kickerSubsystem.stop();
			break;
		case kReturning:
			kickerSubsystem.setDone(false);
			if(timer.hasPeriodPassed(RETRACT_TIME)) {
				this.setState(State.kIdle);
				break;
			}
			System.out.printf("Retracting %f\n", timer.get());
			kickerSubsystem.retract();
			break;
		case kStopped:
			//Something bad happened, do nothing.
			System.out.println("Kicker is stopped");
			kickerSubsystem.setDone(false);
			break;
		default:
			this.setState(State.kStopped);
			System.out.printf("Unknown state %s, stopping kicker\n", this.getState().name());
			break;
		}
    	
    	SmartDashboard.putString("Kicker Supervisor state", this.getState().name());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
   protected void end() {
    	kickerSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
	protected void interrupted() {
    	kickerSubsystem.stop();
    }
    
	private State getState() {
		return kickerSubsystem.getState();
	}
	
    private void setState(State state) {
    	kickerSubsystem.setState(state);
    }
}
