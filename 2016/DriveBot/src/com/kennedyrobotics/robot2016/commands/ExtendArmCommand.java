package com.kennedyrobotics.robot2016.commands;

import com.kennedyrobotics.robot2016.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class ExtendArmCommand extends Command {

    public ExtendArmCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.armSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	System.out.println("[ExtendArmCommand] Stopping arm");
    	Robot.armSubsystem.stopArm();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	System.out.println("[ExtendArmCommand] Extending arm");
    	Robot.armSubsystem.extendArm();
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	System.out.println("[ExtendArmCommand] Ending Stopping arm");
    	Robot.armSubsystem.stopArm();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	System.out.println("[ExtendArmCommand] Interrupted Stopping arm");
    	Robot.armSubsystem.stopArm();
    }
}
