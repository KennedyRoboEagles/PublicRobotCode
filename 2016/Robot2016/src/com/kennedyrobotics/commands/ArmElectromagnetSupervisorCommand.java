package com.kennedyrobotics.commands;

import com.kennedyrobotics.Robot;

import edu.wpi.first.wpilibj.command.Command;

/**
 *
 */
public class ArmElectromagnetSupervisorCommand extends Command {

    public ArmElectromagnetSupervisorCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.armElectromagnetSubsystem);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.armElectromagnetSubsystem.setRelay(false);
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	Robot.armElectromagnetSubsystem.setRelay(Robot.armElectromagnetSubsystem.isArmPresent());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.armElectromagnetSubsystem.setRelay(false);
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.armElectromagnetSubsystem.setRelay(false);
    }
}
