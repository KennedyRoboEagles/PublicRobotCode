package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.RobotMap;
import com.kennedyrobotics.commands.ArmElectromagnetSupervisorCommand;

import edu.wpi.first.wpilibj.Relay;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ArmElectromagnetSubsystem extends Subsystem {
    
	private final Relay electromagnet = new Relay(RobotMap.ELECTROMAGNET_RELAY);

    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	//setDefaultCommand(new ArmElectromagnetSupervisorCommand());
    }
    
    public void setRelay(boolean on) {
    	if(on) {
    		electromagnet.set(Relay.Value.kForward);
    	} else {
    		electromagnet.set(Relay.Value.kOff);
    	}
    }
    
    public boolean isArmPresent() {
    	return Robot.sensorSubsystem.getArmPresentLimit();
    }

}

