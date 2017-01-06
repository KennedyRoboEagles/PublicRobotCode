package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.RobotMap;
import com.kennedyrobotics.commands.shooter.AimShooterUpCommand;
import com.kennedyrobotics.commands.shooter.ShooterAimSupervisorCommand.State;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 * Note: The encoder needs to count down when moving down, up when moving up.
 */
public class ShooterAimSubsystem extends Subsystem {
    
	public static final double LOW_ANGLE = 0;
	public static final double HIGH_ANGLE = 90;

	private final DoubleSolenoid solenoid = new DoubleSolenoid(RobotMap.SHOOTER_AIM_FORWARD, RobotMap.SHOOTER_AIM_BACKWARD);
	
	private boolean onTarget;
	private double  desiredAngle;
	private State state = State.kStartCalibration;
		
	public ShooterAimSubsystem() {
	}
	
	public boolean inCalibration() {
		return this.state.calibration; 
	}
	
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	//setDefaultCommand(new ShooterAimSupervisorCommand());
    	setDefaultCommand(new AimShooterUpCommand());
    }
    
    
    public void stop() {
    	solenoid.set(DoubleSolenoid.Value.kOff);
    }
    
    public boolean lowLimit() {
    	return Robot.sensorSubsystem.getShooterAimLowLimit();
    }
  
    public boolean highLimit() {
    	return Robot.sensorSubsystem.getShooterAimHighLimit();
    }

 	public void down() {
    	solenoid.set(DoubleSolenoid.Value.kReverse);
    }
    
 	public void up() {
    	solenoid.set(DoubleSolenoid.Value.kForward);
 	}
  	
 	public Encoder getEncoder() {
 		return Robot.sensorSubsystem.getShooterAimEncoder();
 	}
 	
 	public double getCurrentTiltAngle() {
 		return HIGH_ANGLE - this.getEncoder().getDistance();
 	}
 	
 	

 	//The following are used to alter the state of the supervisor
 	
 	public void setDesiredTiltAngle(double angle) {
		if(angle < LOW_ANGLE) {
 			desiredAngle = LOW_ANGLE;
 		} else if(HIGH_ANGLE < angle){
 			desiredAngle = HIGH_ANGLE;
 		} else {
 			desiredAngle = angle;
 		}
 
 				
 		this.onTarget = false;
 	}
 	
	public double getDesiredTiltAngle() {
		return desiredAngle;
	}

	public boolean getOnTarget() {
		return onTarget;
	}

 	//The following methods are only to be used by the Supervisor
 	
	public State getState() {
    	return this.state;
    }
	
	public void setState(State state) {
		this.state = state;
	}

	public void setOnTarget(boolean onTarget) {
		this.onTarget = onTarget;
	}
}

