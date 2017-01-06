package org.usfirst.frc.team3081.robot.commands;

import org.usfirst.frc.team3081.robot.subsystems.ArmSubsystem;

import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

import static org.usfirst.frc.team3081.robot.Robot.armSubsystem;

import org.usfirst.frc.team3081.robot.Robot;

/**
 *
 */
public class MoveArmToPositionCommand extends Command {

	public static final double TOLLERANCE = 0.25;
	
	public static final double P_GAIN = 0.0;
	public static final double I_GAIN = 0.0;
	public static final double D_GAIN = 0.0;
	
	private final PIDController controller;
	
	private final double setpoint;
	
	private boolean finished = false;
	
    public MoveArmToPositionCommand(double setpoint) {
    	this.setpoint = setpoint;

        // Use requires() here to declare subsystem dependencies
        // eg. requires(chassis);
    	requires(armSubsystem);
    	
    	controller = new PIDController(P_GAIN, I_GAIN, D_GAIN, armSubsystem.getEncoder(), armSubsystem.getMotor());
    
    	controller.setInputRange(ArmSubsystem.ARM_MIN_LENGTH, ArmSubsystem.ARM_MAX_LENGTH);
    	controller.setOutputRange(-1.0, 1.0);
    	controller.setAbsoluteTolerance(TOLLERANCE);
  
    	controller.setSetpoint(this.setpoint);
    	
    	controller.reset();
  
    	
    }

    // Called just before this Command runs the first time
    protected void initialize() {
    	finished = false;
    	
    	armSubsystem.stop();
    	controller.reset();
    	controller.setSetpoint(setpoint);
    	controller.enable();
    }

    // Called repeatedly when this Command is scheduled to run
    protected void execute() {
    	if(armSubsystem.lowLimit() || armSubsystem.highLimit()) {
    		armSubsystem.stop();
    		finished = true;
    	}
    	
    	finished = controller.onTarget();
    	
    	System.out.println(
    			"Setpoint "+ controller.getSetpoint()+ 
    			" current " + armSubsystem.getEncoder().pidGet() + 
    			" Erorr " + controller.getError() + 
    			" Output " + controller.get());
    	
    	SmartDashboard.putNumber("Arm Setpoint", controller.getSetpoint());
    	SmartDashboard.putNumber("Arm Current Position", armSubsystem.getEncoder().pidGet());
    	SmartDashboard.putNumber("Arm Error", controller.getError());
    	SmartDashboard.putNumber("Arm output", controller.get());
    }

    // Make this return true when this Command no longer needs to run execute()
    protected boolean isFinished() {
        return finished;
    }

    // Called once after isFinished returns true
    protected void end() {
    	controller.disable();
    	armSubsystem.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    protected void interrupted() {
    	controller.disable();
    	armSubsystem.stop();
    }
}
