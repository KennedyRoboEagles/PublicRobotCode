package org.usfirst.frc.team3081.robot.commands;

import org.usfirst.frc.team3081.robot.Robot;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 *
 */
public class ShooterCommand extends Command {

    public ShooterCommand() {
        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(Robot.shooterSubsystem);
    	SmartDashboard.putNumber("Left", 0.0);
    	SmartDashboard.putNumber("Right", 0.0);

    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.shooterSubsystem.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	double left = SmartDashboard.getNumber("Left", 0.0);
    	double right = SmartDashboard.getNumber("Right", 0.0);
    	System.out.printf("Left %f, Right %f\n", left, right);
    	Robot.shooterSubsystem.set(left, right);
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.shooterSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.shooterSubsystem.stop();
    }
}
