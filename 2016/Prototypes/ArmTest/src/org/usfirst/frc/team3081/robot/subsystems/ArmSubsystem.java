package org.usfirst.frc.team3081.robot.subsystems;

import org.usfirst.frc.team3081.robot.Robot;

import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.PIDSourceType;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ArmSubsystem extends Subsystem {
    
	public static class ArmEncoder implements PIDSource {

		private final Encoder encoder;
		public ArmEncoder(Encoder encoder) {
			this.encoder = encoder;
		}
		
		@Override public void setPIDSourceType(PIDSourceType pidSource) {}

		@Override
		public PIDSourceType getPIDSourceType() {
			return PIDSourceType.kDisplacement;
		}

		@Override
		public double pidGet() {
			return Robot.sensorSubsystem.getArmEncoder().getDistance() + ARM_MIN_LENGTH;
		}
		
		public Encoder getEncoder() {
			return encoder;
		}
		
	}
	
	public static final double ARM_MAX_LENGTH = 10;
	public static final double ARM_MIN_LENGTH = 5;

	private final ArmEncoder encoder = new ArmEncoder(Robot.sensorSubsystem.getArmEncoder());
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public boolean lowLimit() {
     return false;
    }
    public boolean highLimit() {
        return false;
       }
       
    public SpeedController getMotor() {
    	return null;
    }
    
    public ArmEncoder getEncoder() {
    	return encoder;
    }
    
    public void stop() {
    	
    }
    
    
}

