package org.usfirst.frc.team3081.robot.subsystems;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.PIDSourceType;
import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class SensorSubsystem extends Subsystem {
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private Encoder armEncoder = new Encoder(0,1, false, EncodingType.k4X);
	
	public SensorSubsystem() {
		armEncoder.setPIDSourceType(PIDSourceType.kDisplacement);
	}
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    
    }
    
    public Encoder getArmEncoder() {
    	return armEncoder;
    }
    
    
}

