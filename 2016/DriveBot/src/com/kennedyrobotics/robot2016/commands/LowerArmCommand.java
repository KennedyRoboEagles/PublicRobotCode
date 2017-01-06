package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class LowerArmCommand extends Command {

    public LowerArmCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.armTiltSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("[LowerArmCommand] Stopping tilt");
    	Robot.armTiltSubsystem.stopArm();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(Robot.armTiltSubsystem.isAtLowLimt()){
        	System.out.println("[LowerArmCommand] At low limit Stopping");
    		Robot.armTiltSubsystem.stopArm();
    	} else {
        	System.out.println("[LowerArmCommand] Lowering arm");
    		Robot.armTiltSubsystem.lowerArm();
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Robot.armTiltSubsystem.isAtLowLimt();
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[LowerArmCommand] Ending Stoping tilt");
    	Robot.armTiltSubsystem.stopArm();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[LowerArmCommand] Interrupted stopping tilt");
    	Robot.armTiltSubsystem.stopArm();
    }
}
