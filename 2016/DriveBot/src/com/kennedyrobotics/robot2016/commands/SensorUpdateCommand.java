package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

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
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(!imuInit) {
			if(!Robot.sensorSubsystem.getNavX().isCalibrating()) {
				System.out.println("[SensorUpdateCommand] navX calibrated");
				imuInit = true;
			} else {
				System.out.println("[SensorUpdateCommand] Waiting for navX to be calibrated");
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
	
    	SmartDashboard.putNumber("Chassis Left Encoder", Robot.sensorSubsystem.getChassisLeftEncoder().getDistance());
    	SmartDashboard.putNumber("Chassis Right Encoder", Robot.sensorSubsystem.getChassisRightEncoder().getDistance());
    	
    	SmartDashboard.putBoolean("Aim Tilt Low limit", Robot.armTiltSubsystem.isAtLowLimt());
    	SmartDashboard.putBoolean("Aim Tilt High Limit", Robot.armTiltSubsystem.isAtHighLimit());
    	
    	SmartDashboard.putNumber("Yaw Angle", Robot.sensorSubsystem.getYaw());
    	
    	SmartDashboard.putBoolean("NavX Connected", Robot.sensorSubsystem.getNavX().isConnected());
    	SmartDashboard.putBoolean("NavX Calibrating", Robot.sensorSubsystem.getNavX().isCalibrating());

    	SmartDashboard.putNumber("NavX Yaw", Robot.sensorSubsystem.getNavX().getYaw());
    	SmartDashboard.putNumber("NavX Pitch", Robot.sensorSubsystem.getNavX().getPitch());
    	SmartDashboard.putNumber("NavX Roll", Robot.sensorSubsystem.getNavX().getRoll());
    	SmartDashboard.putNumber("NavX Compas Heading", Robot.sensorSubsystem.getNavX().getCompassHeading());
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
