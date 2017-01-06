package com.kennedyrobotics.commands.drive;

import com.kennedyrobotics.Robot;
import com.kennedyrobotics.RobotMap;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;


/**
 *
 */
public class DriveWithJoystick extends Command {
	public static final double SHOOTER_THRESHOLD = 0.3;
	public static final double SHOOTER_ROTATE = 0.5;
	

    public DriveWithJoystick() {
    	requires(Robot.chassis);
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	Robot.chassis.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	
    	double x = Robot.oi.getDriverStick().getX();
    	double y = Robot.oi.getDriverStick().getY();
    	double shooterX = Robot.oi.getShooterStick().getRawAxis(4);
    	SmartDashboard.putNumber("Joystick X", x);
    	SmartDashboard.putNumber("Joystick Y", y);
    	
		//Deadzone
		if(Math.abs(x) < 0.1) {
			x = 0;
		}
		
		if(Math.abs(y) < 0.1) {
			y = 0;
		}
		
		
		//Swaps the front and back
		if(Robot.oi.getDriverStick().getRawButton(RobotMap.OI_DRIVER_SWAP)) {
			y = -y;
		}
		
		if(shooterX < -SHOOTER_THRESHOLD) {
			x = -SHOOTER_ROTATE;
		} else if(SHOOTER_THRESHOLD < shooterX){
			x = SHOOTER_ROTATE;
		}
		
		x = -x;//?
    	Robot.chassis.arcadeDrive(y,x);    	
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    protected void end() {
    	Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	Robot.chassis.stop();
    }
}
