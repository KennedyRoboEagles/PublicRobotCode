package org.usfirst.frc.team3081.robot.subsystems;

import org.usfirst.frc.team3081.robot.Robot;
import org.usfirst.frc.team3081.robot.RobotMap;

import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class ShooterAimSubsystem extends Subsystem {
    
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final SpeedController controller = new Jaguar(RobotMap.AIM_SHOOTER);
	
    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    }
    
    public void set(double speed) {
    	controller.set(speed);
    }
    
    public void stop() {
    	controller.set(0.0);
    }
    
  
}

