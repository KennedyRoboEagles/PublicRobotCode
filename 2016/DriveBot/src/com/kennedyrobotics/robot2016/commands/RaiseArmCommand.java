package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class RaiseArmCommand extends Command {

    public RaiseArmCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.armTiltSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("[RaiseArmCommand] Stopping tilt");
    	Robot.armTiltSubsystem.stopArm();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(Robot.armTiltSubsystem.isAtHighLimit()) {
        	System.out.println("[RaiseArmCommand] Stopping at high limit");
    		Robot.armTiltSubsystem.stopArm();
    	} else {
        	System.out.println("[RaiseArmCommand] Raising");
    		Robot.armTiltSubsystem.raiseArm();
    	}
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return Robot.armTiltSubsystem.isAtHighLimit();
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[RaiseArmCommand] End Stopping tilt");
		Robot.armTiltSubsystem.stopArm();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[RaiseArmCommand] Interruptped Stopping tilt");
		Robot.armTiltSubsystem.stopArm();
    }
}
