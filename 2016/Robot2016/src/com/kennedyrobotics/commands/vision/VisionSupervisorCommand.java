package com.kennedyrobotics.commands.vision;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class VisionSupervisorCommand extends Command {
	
	public VisionSupervisorCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.visionSubsystem);
    	setRunWhenDisabled(true);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	SmartDashboard.putBoolean("VisionX", false);
    	SmartDashboard.putBoolean("VisionY", false);
    	SmartDashboard.putBoolean("VisionA", false);
    	SmartDashboard.putBoolean("VisionB", false);
    	SmartDashboard.putBoolean("VisionC", false);
    	
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.visionSubsystem.getTask().enableProcessing();
    	SmartDashboard.putBoolean("Target", Robot.visionSubsystem.getTask().isTargetPresent());
    	SmartDashboard.putNumber("Target Distance", Robot.visionSubsystem.getTask().getTargetDistance());
    	SmartDashboard.putBoolean("Processing", Robot.visionSubsystem.getTask().isProcessing());
//    	SmartDashboard.putNumber("Vision Angle To target", Robot.visionSubsystem.computeAngleToTurn());
    	
    	double distance = Robot.visionSubsystem.getTask().getTargetDistance();
    	double comX = Robot.visionSubsystem.getTask().getTargetcomX();
    	
    	double distanceLowEnd = 9;
    	double distanceHighEnd = 10;
    	double comXLow = 640/2 - 15;
    	double comXHigh = 640/2 + 15;
    	
    	boolean a;
    	boolean c;
    	boolean x;
    	boolean y;
    	
    	if(distance < distanceLowEnd) {
    		//Too close
    		x = true;
    		y = false;
    	} else if (distanceHighEnd < distance) {
    		//Too Far away
    		x = false;
    		y = true;
    	} else {
    		//Just right
    		x = true;
    		y = true;
    	}
    	
    	if(comX < comXLow) {
    		//The target is to the left
    		a = false;
    		c = true;
    	} else if (comXHigh < comX) {
    		//THe target is to the right
    		a = true;
    		c = false;
    	} else {
    		//The Target is in the center
    		a = true;
    		c = true;
    	}

    	boolean b = a && c && x && y;
    	
    	SmartDashboard.putBoolean("VisionX", x);
    	SmartDashboard.putBoolean("VisionY", y);
    	SmartDashboard.putBoolean("VisionA", a);
    	SmartDashboard.putBoolean("VisionB", b);
    	SmartDashboard.putBoolean("VisionC", c);
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
