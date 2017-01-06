package com.kennedyrobotics.subsystems;

import com.kennedyrobotics.commands.vision.VisionSupervisorCommand;
import com.kennedyrobotics.vision.Vision2016;
import com.kennedyrobotics.vision.VisionTask;

import edu.wpi.first.wpilibj.command.Subsystem;

/**
 *
 */
public class VisionSubsystem extends Subsystem {
    
	private final VisionTask task;
	
	public VisionTask getTask() {
		return task;
	}
	
	public VisionSubsystem() {
		task = new VisionTask();
		task.start();
		task.enableProcessing();
	}
	
    // Put methods for controlling this subsystem
    // here. Call these from Commands.

    public void initDefaultCommand() {
        // Set the default command for a subsystem here.
        //setDefaultCommand(new MySpecialCommand());
    	setDefaultCommand(new VisionSupervisorCommand());
    }
    
    public double calculateShootAngle() {
    	return this.calculateShootAngle(this.task.getTargetDistance(), 4);
    }
    
    public double calculateShootAngle(double distance, double targetHieght) {
    	if(distance <=0) {
    		return -1;
    	}
    	return Math.toDegrees(Math.atan(targetHieght / distance));
    }
    
    public double computeAngleToTurn() {
    	if(task.isTargetPresent()) {
    		return computeAngleToTurn(task.getTargetDistance(), task.getTargetcomX());
    	} else {
    		return 0;
    	}
    }
    
    public double computeAngleToTurn(double distance, double comX) {
//		double fov = 2*distance * Math.atan(Math.toRadians(1/2*Vision2016.VIEW_ANGLE));
//		double ftPerPix = fov/640;
//		double delta = 640/2 - comX;
//		delta *= ftPerPix;
//		return Math.toDegrees(Math.atan2(distance, delta));
    	return 0;
	}
}

