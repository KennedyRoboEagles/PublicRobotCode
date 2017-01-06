package com.kennedyrobotics.robot2016.subsystems;

import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.robot2016.RobotMap;
import com.kennedyrobotics.robot2016.commands.SensorUpdateCommand;

import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Encoder;
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

	private final Encoder chassisLeftEncoder = new Encoder(
			RobotMap.CHASSIS_ENCODER_LEFT_A, 
			RobotMap.CHASSIS_ENCODER_LEFT_B, 
			false, 
			EncodingType.k4X);
	private final Encoder chassisRightEncoder = new Encoder(
			RobotMap.CHASSIS_ENCODER_RIGHT_A, 
			RobotMap.CHASSIS_ENCODER_RIGHT_B, 
			false, 
			EncodingType.k4X);
	private final DigitalInput aimArmTiltLowLimit = new DigitalInput(RobotMap.ARM_TILT_LOW_LIMIT);
	private final DigitalInput aimArmTiltHighLimit = new DigitalInput(RobotMap.ARM_TILT_HIGH_LIMIT);
	private final DigitalInput shooterAimTiltLowLimit = new DigitalInput(RobotMap.BALL_SHOOTER_TILT_LOW_LIMIT);
	private final DigitalInput shooterAimTiltHighLimit = new DigitalInput(RobotMap.BALL_SHOOTER_TILT_HIGH_LIMIT);
	
	private AHRS navX;
	private boolean collision = false;
		
	public SensorSubsystem() {
		chassisLeftEncoder.setDistancePerPulse(DRIVE_INCH_PER_COUNT);
		chassisLeftEncoder.setMaxPeriod(1.0);
		chassisLeftEncoder.reset();
		
		chassisRightEncoder.setDistancePerPulse(DRIVE_INCH_PER_COUNT);
		chassisRightEncoder.setMaxPeriod(1.0);
		chassisRightEncoder.reset();
		
		try {
			navX = new AHRS(SerialPort.Port.kMXP);
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
    
    public boolean getArmAimTiltLowLimit(){
    	return aimArmTiltLowLimit.get();
    }
    
    public boolean getArmAimTiltHighLimit(){
    	return aimArmTiltHighLimit.get();
    }
    
    public boolean getShooterAimTiltHighLimit(){
    	return shooterAimTiltHighLimit.get();
    }
    
    public boolean getShooterAimTiltLowLimit(){
    	return shooterAimTiltLowLimit.get();
    }
    
	public Encoder getChassisLeftEncoder() {
		return chassisLeftEncoder;
	}
	
	public Encoder getChassisRightEncoder() {
		return chassisRightEncoder;
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
}

