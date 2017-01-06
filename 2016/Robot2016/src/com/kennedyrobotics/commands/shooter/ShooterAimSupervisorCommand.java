package com.kennedyrobotics.commands.shooter;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.subsystems.ShooterAimSubsystem;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 * Note: Will Calibrate Shooter to its upward position
 */
public class ShooterAimSupervisorCommand extends Command {
	
	public enum State {
		kStartCalibration(true),
		kCalibration(true),
		kEndCalibration(true),
		kRunning,
		kCalibrationError,
		kError;
		
		public final boolean calibration;
		
		private State(boolean calibration) {
			this.calibration = calibration;
		}
		
		private State() {
			this(false);
		}
	}
	public static final double TIME_OUT = 5;
	public static final double TOLLERANCE = 3;//Degrees
	
	
	private final Timer timer = new Timer();

	private double setpoint;
	
    public ShooterAimSupervisorCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.shooterAimSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	if(this.getState() == State.kError || this.getState() == State.kCalibrationError) {
    		//Leave the state in kError or kCalibratoinError
    	} else if(this.getState() == State.kRunning) {
    		this.setState(State.kRunning);
    	} else {
    		this.setState(State.kStartCalibration);
    	}
    }

	// Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	boolean onTarget = false;
    	double currentAngle = Robot.shooterAimSubsystem.getCurrentTiltAngle();
    	double delta = currentAngle - Robot.shooterAimSubsystem.getDesiredTiltAngle();
    	
      	switch(this.getState()) {
    	case kStartCalibration:
    		if(Robot.shooterAimSubsystem.highLimit()) {
        		System.out.printf("[ShooterAimSupervisor] Shooter is already at high limit, calibrated\n");
        		this.setState(State.kEndCalibration);
        		break;
        	}
    	 	System.out.printf("[ShooterAimSupervisor] Starting timeout timer\n");
        	timer.reset();
        	timer.start();
        	
        	this.setState(State.kCalibration);
       
    		break;
    	case kCalibration:
    		if(Robot.shooterAimSubsystem.highLimit()) {
        		System.out.printf("[ShooterAimSupervisor] reached high position, calibrated\n");
            	this.setState(State.kEndCalibration);
        		break;
        	}
        	
//        	if(Robot.shooterAimSubsystem.lowLimit()) {
//        		System.out.printf("[ShooterAimSupervisor] reached low position disabling\n");
//        		//Should not be here
//            	this.setState(State.kCalibrationError);
//        		break;
//        	}
        	
        	if(timer.hasPeriodPassed(TIME_OUT)) {
        		System.out.printf("[ShooterAimSupervisor] timed out disabling\n");
        		//Shooter tilt has timed out
            	this.setState(State.kCalibrationError);
        		break;
        	}
        	
    		System.out.printf("[ShooterAimSupervisor] Shooter raising, time %f\n", timer.get());
         	Robot.shooterAimSubsystem.up();
            break;
    	case kEndCalibration:
    		timer.stop();
        	System.out.printf("[ShooterAimSupervisor] Calibrated, stopping shooter, and resetting encoder\n");
        	System.out.printf("[ShooterAimSupervisor] Stopping, and resetting encoder\n");
        	Robot.shooterAimSubsystem.stop();
        	Robot.shooterAimSubsystem.getEncoder().reset();
        	Robot.shooterAimSubsystem.setDesiredTiltAngle(ShooterAimSubsystem.HIGH_ANGLE);
        	System.out.printf("Desired Tilt Angle %f", Robot.shooterAimSubsystem.getDesiredTiltAngle());
        	this.setState(State.kRunning);
        
    	case kRunning:
    		if(Robot.shooterAimSubsystem.lowLimit() && Robot.shooterAimSubsystem.getDesiredTiltAngle() <= ShooterAimSubsystem.LOW_ANGLE) {
        		System.out.println("[ShooterAimSupervisor] Reached low limit, disabling controller, resetting encoder");
        		Robot.shooterAimSubsystem.stop();
        		onTarget = true;
        	} else if(Robot.shooterAimSubsystem.highLimit() && Robot.shooterAimSubsystem.getDesiredTiltAngle() >= ShooterAimSubsystem.HIGH_ANGLE) {
        		System.out.println("[ShooterAimSupervisor] Reached extend limit, disabling controller");
        		Robot.shooterAimSubsystem.stop();
        		//We want to reset the encoder when it is at one of its known locations to help prevent drift/error in the angle
        		//of the shooter tilt over time, when the the shooter moves up and down.
        		Robot.shooterAimSubsystem.getEncoder().reset();
        		onTarget = true;
    		} else if(delta > TOLLERANCE) {
    			//Move down
    			Robot.shooterAimSubsystem.down();
    			onTarget = false;
    		} else if(delta < -TOLLERANCE) {
    			//Move Up
    			Robot.shooterAimSubsystem.up(); 			
    			onTarget = false;
    		} else {
    			//In Place
    			Robot.shooterAimSubsystem.stop();
    			onTarget = true;
    		}
    		
    		System.out.println(
        			"[ShooterAimSupervisor]: Setpoint " + Robot.shooterAimSubsystem.getDesiredTiltAngle()+ 
        			" current " + currentAngle + 
        			" Erorr " + delta);
           		break;
    	case kError:
    	case kCalibrationError:
    		timer.stop();
    		Robot.shooterAimSubsystem.stop();
    		break;
    	default: 
    		this.setState(State.kError);
    		break;
    	}
      	
      	setpoint = Robot.shooterAimSubsystem.getDesiredTiltAngle();
      	
      	Robot.shooterAimSubsystem.setOnTarget(onTarget);
      	
      	SmartDashboard.putNumber("Shooter Aim Setpoint", setpoint);
    	SmartDashboard.putNumber("Shooter Aim Current Angle", currentAngle);
    	SmartDashboard.putNumber("Shooter Aim Error", delta);
    	SmartDashboard.putBoolean("Shooter Aim OnTarget", onTarget);
  
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[ShooterAimSupervisor] Ending");
		Robot.shooterAimSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[ShooterAimSupervisor] Interupted");
    	Robot.shooterAimSubsystem.stop();
	}

    private void setState(State state) {
    	Robot.shooterAimSubsystem.setState(state);
    }
    
    private State getState() {
    	return Robot.shooterAimSubsystem.getState();
    }
}
