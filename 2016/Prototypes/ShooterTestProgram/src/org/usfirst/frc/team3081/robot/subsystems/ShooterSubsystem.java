package org.usfirst.frc.team3081.robot.subsystems;

import org.usfirst.frc.team3081.robot.RobotMap;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ShooterSubsystem extends Subsystem {
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final SpeedController left = new Jaguar(RobotMap.RIGHT_SHOOTER);
	private final SpeedController right = new Jaguar(RobotMap.LEFT_SHOOTER);
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public void stop() {
    	this.set(0.0, 0.0);
    }
    
    public void set(double leftspeed, double rightspeed) {
    	left.set(leftspeed);
    	right.set(rightspeed);
    }
}

