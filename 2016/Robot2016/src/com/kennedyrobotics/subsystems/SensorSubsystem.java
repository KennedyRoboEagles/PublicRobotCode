package com.kennedyrobotics.subsystems;

import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.RobotMap;
import com.kennedyrobotics.commands.SensorUpdateCommand;

import edu.wpi.first.wpilibj.CounterBase.EncodingType;
import edu.wpi.first.wpilibj.DigitalInput;
import edu.wpi.first.wpilibj.DigitalOutput;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Encoder;
import edu.wpi.first.wpilibj.SerialPort;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.livewindow.LiveWindow;

/**
 *
 */
public class SensorSubsystem extends Subsystem {
   
	private static final double ENCODER_COUNT = 120;
	private static final double WHEEL_SIZE_INCH = 8;
	
	public static final double DRIVE_INCH_PER_COUNT = Math.PI * WHEEL_SIZE_INCH / ENCODER_COUNT;
	public static final double ARM_INCH_PER_COUNT = 0.1570796327;
	public static final double ARM_AIM_DEGREES_PER_COUNT = 3.0;
	public static final double SHOOTER_AIM_DEGRESS_PER_COUNT = 3.0;
	
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
	
	private Encoder shooterAimEncoder = new Encoder(
			RobotMap.BALL_SHOOTER_TILT_ENCODER_A, 
			RobotMap.BALL_SHOOTER_TILT_ENCODER_B, 
			false, 
			EncodingType.k4X);


//	private final DigitalOutput edgeLed = new DigitalOutput(RobotMap.LED);
	private final DigitalInput lineDedector = new DigitalInput(RobotMap.LINE_DEDECTOR);
	
	private final DigitalInput wallDetector = new DigitalInput(RobotMap.CHASSIS_WALL_DETECTOR);
		
	private final DigitalInput shooterAimLowLimit = new DigitalInput(RobotMap.SHOOTER_TILT_LOW_LIMIT);
	private final DigitalInput shooterAimHighLimit = new DigitalInput(RobotMap.SHOOTER_TILT_HIGH_LIMIT);
	
	private final DigitalInput armLowLimit = new DigitalInput(RobotMap.ARM_LOW_LIMIT);
	private final DigitalInput armHighLimit = new DigitalInput(RobotMap.ARM_HIGH_LIMIT);
	private final DigitalInput armPresentLimit = new DigitalInput(RobotMap.ARM_PRESENT_LIMIT);
	private AHRS navX;
	private boolean collision = false;
		
	public SensorSubsystem() {
		chassisLeftEncoder.setDistancePerPulse(DRIVE_INCH_PER_COUNT);
		chassisLeftEncoder.setMaxPeriod(0.1);
		chassisLeftEncoder.reset();
		
		chassisRightEncoder.setDistancePerPulse(DRIVE_INCH_PER_COUNT);
		chassisRightEncoder.setMaxPeriod(0.1);
		chassisRightEncoder.reset();
		
		shooterAimEncoder.setDistancePerPulse(SHOOTER_AIM_DEGRESS_PER_COUNT);
		shooterAimEncoder.setMaxPeriod(1.0);
		shooterAimEncoder.reset();
		
//		edgeLed.set(true);
		
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
        
	public Encoder getChassisLeftEncoder() {
		return chassisLeftEncoder;
	}
	
	public Encoder getChassisRightEncoder() {
		return chassisRightEncoder;
	}

	public boolean atWall() {
		return !wallDetector.get();
	}
	
	public boolean getShooterAimLowLimit() {
		return !shooterAimLowLimit.get();
	}
	
	public boolean getShooterAimHighLimit() {
		return !shooterAimHighLimit.get();
	}
	
	public Encoder getShooterAimEncoder() {
		return shooterAimEncoder;
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
	
	public AHRS getNavX1(){
		return navX;
	}
	
	public double getPitch(){
		if(navX == null) {
			DriverStation.reportError("NavX is null", false);
			return 0.0;
		} else {
			return navX.getPitch();
		}
	}
	
	public void setCollision(boolean collision){
		this.collision = collision;
	}
	
	public boolean getCollision(){
		return collision;
	}

	public boolean isLevel(){
		return Math.abs(navX.getPitch()) < 10.0;
	}

	public void setEdgeLed(boolean value) {
//		edgeLed.set(value);
	}
	
	public boolean getLineDedector() {
		return lineDedector.get();
	}
	
	public boolean getArmLowLimit() {
		return armLowLimit.get();
	}
	
	public boolean getArmHighLimit() {
		return armHighLimit.get();
	}
	
	public boolean getArmPresentLimit() {
		return armPresentLimit.get();
	}
}

