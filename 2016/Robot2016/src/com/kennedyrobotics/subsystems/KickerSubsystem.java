package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.RobotMap;
import com.kennedyrobotics.commands.kicker.KickerSupervisorCommand;
import com.kennedyrobotics.commands.kicker.KickerSupervisorCommand.State;

import edu.wpi.first.wpilibj.DoubleSolenoid;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class KickerSubsystem extends Subsystem {
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final DoubleSolenoid solenoid = new DoubleSolenoid(
			RobotMap.KICKER_SOLENOID_FORWARD, RobotMap.KICKER_SOLENOID_REVERSE);
	
	private boolean done = false;
	private boolean calibrated = false;

	private KickerSupervisorCommand.State state;

	public KickerSupervisorCommand.State getState() {
		return state;
	}
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
		//setDefaultCommand(new KickerSupervisorCommand());
    }
    
    public void kickBall() {
    	if(this.state == State.kIdle) {
        	this.done = false;
        	this.state = State.kStartKick;
    	}
    }
    
    public boolean isDone() {
    	return this.done;
    }
    
    public boolean isCalibrated() {
    	return this.calibrated;
    }
    
    
    //
    // The following methods are to be used only by the 
    // Kicker Supervisor Command
    //
    
    public void setDone(boolean done) {
    	this.done = done;
    }
    
    public void setCalibrated(boolean cal) {
    	this.calibrated = cal;
    }
    
    public void setState(KickerSupervisorCommand.State state) {
    	this.state = state;
    }
    
    public void extend() {
    	solenoid.set(DoubleSolenoid.Value.kForward);
    }
    
    public void retract() {
    	solenoid.set(DoubleSolenoid.Value.kReverse);
    }
    
    public void stop() {
    	solenoid.set(DoubleSolenoid.Value.kOff);
    }
}

