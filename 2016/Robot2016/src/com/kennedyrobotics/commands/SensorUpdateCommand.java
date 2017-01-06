package com.kennedyrobotics.commands;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class SensorUpdateCommand extends Command {

	private boolean imuInit = false;
	
    public SensorUpdateCommand() {
    	requires(Robot.sensorSubsystem);
    }
    
    private double last_world_linear_accel_x;
    private double last_world_linear_accel_y;
    public final static double kCollisionThreshold_DeltaG = 0.5f;


    // Called just before this Command runs the first time
    protected void initialize() {
    	imuInit = false;
    	Robot.sensorSubsystem.setEdgeLed(true);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(!imuInit) {
			if(!Robot.sensorSubsystem.getNavX().isCalibrating()) {
				System.out.println("[SensorUpdateCommand] navX calibrated");
				imuInit = true;
			} else {
				//System.out.println("[SensorUpdateCommand] Waiting for navX to be calibrated");
			}
	    }
    	
    	boolean collisionDetected = false;
        
        double curr_world_linear_accel_x = Robot.sensorSubsystem.getNavX().getWorldLinearAccelX();
        double currentJerkX = curr_world_linear_accel_x - last_world_linear_accel_x;
        last_world_linear_accel_x = curr_world_linear_accel_x;
        double curr_world_linear_accel_y = Robot.sensorSubsystem.getNavX().getWorldLinearAccelY();
        double currentJerkY = curr_world_linear_accel_y - last_world_linear_accel_y;
        last_world_linear_accel_y = curr_world_linear_accel_y;
        
        if ( ( Math.abs(currentJerkX) > kCollisionThreshold_DeltaG ) ||
             ( Math.abs(currentJerkY) > kCollisionThreshold_DeltaG) ) {
            collisionDetected = true;
        }
        
        Robot.sensorSubsystem.setCollision(collisionDetected);
        SmartDashboard.putBoolean("Collision detected", collisionDetected);

        //Chasis
    	SmartDashboard.putNumber("Chassis Left Encoder", Robot.sensorSubsystem.getChassisLeftEncoder().getDistance());
    	SmartDashboard.putNumber("Chassis Right Encoder", Robot.sensorSubsystem.getChassisRightEncoder().getDistance());
    	
    	SmartDashboard.putNumber("Chassis Left Rate", Robot.sensorSubsystem.getChassisLeftEncoder().getRate());
    	SmartDashboard.putNumber("Chassis Right Rate", Robot.sensorSubsystem.getChassisRightEncoder().getRate());

    	SmartDashboard.putNumber("Chassis Left Encoder Samples", Robot.sensorSubsystem.getChassisLeftEncoder().getSamplesToAverage());
    	SmartDashboard.putNumber("Chassis Right Encoder Samples", Robot.sensorSubsystem.getChassisRightEncoder().getSamplesToAverage());
    	
    	//Arm
//    	SmartDashboard.putBoolean("Arm Aim Low Limit", Robot.sensorSubsystem.getArmTiltLowLimit());
//    	SmartDashboard.putBoolean("Arm Aim High Limit", Robot.sensorSubsystem.getArmTiltHighLimit());
    	//Shooter
    	SmartDashboard.putBoolean("Shooter Aim Low Limit", Robot.sensorSubsystem.getShooterAimLowLimit());
    	SmartDashboard.putBoolean("Shooter Aim High Limit", Robot.sensorSubsystem.getShooterAimHighLimit());
    	SmartDashboard.putNumber("Shooter Aim Encoder Position", Robot.sensorSubsystem.getShooterAimEncoder().getDistance());

    	SmartDashboard.putBoolean("Line Dedector", Robot.sensorSubsystem.getLineDedector());;
    	
    	//Nav X
    	SmartDashboard.putBoolean("NavX Connected", Robot.sensorSubsystem.getNavX().isConnected());
    	SmartDashboard.putBoolean("NavX Calibrating", Robot.sensorSubsystem.getNavX().isCalibrating());
    	SmartDashboard.putNumber("NavX Yaw", Robot.sensorSubsystem.getNavX().getYaw());
    	SmartDashboard.putNumber("NavX Pitch", Robot.sensorSubsystem.getNavX().getPitch());
    	SmartDashboard.putNumber("NavX Roll", Robot.sensorSubsystem.getNavX().getRoll());
    	SmartDashboard.putNumber("NavX Compas Heading", Robot.sensorSubsystem.getNavX().getCompassHeading());
    	SmartDashboard.putNumber("Yaw Angle", Robot.sensorSubsystem.getYaw());
    	
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    }
}
