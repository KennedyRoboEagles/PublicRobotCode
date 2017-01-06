package com.kennedyrobotics.robot2016.subsystems;

import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.robot2016.RobotMap;
import com.kennedyrobotics.robot2016.commands.SensorUpdateCommand;

import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.SerialPort;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

/**
 *
 */
public class SensorSubsystem extends Subsystem {
    
	public static final double DRIVE_INCH_PER_COUNT = 0.1570796327;
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

	private final DigitalInput wallDetector = new DigitalInput(RobotMap.CHASSIS_WALL_DEDECTOR);
	
	private AHRS navX;
	private boolean collision = false;
		
	public SensorSubsystem() {
		
		try {
			navX = new AHRS(SerialPort.Port.kUSB);
		} catch (Exception e) {
			DriverStation.reportError("Error instantiating navX MXP:  " + e.getMessage(), true);
			navX = null;
		}
		if(navX != null) {
			LiveWindow.addSensor("IMU", "Gyro", navX);
		}
	}
	
    public void initDefaultCommand() {
    	setDefaultCommand(new SensorUpdateCommand());
    }
    
    public AHRS getNavX() {
    	return navX;
    }
    
	public double getYaw() {
		if(navX == null) {
			DriverStation.reportError("NavX is null", false);
			return 0.0;
		} else {
			return navX.getYaw();

		}
	}
	
	public void setCollision(boolean collision){
		this.collision = collision;
	}
	
	public boolean getCollision(){
		return collision;
	}
	
	public boolean atWall() {
		return !wallDetector.get();
	}
}

