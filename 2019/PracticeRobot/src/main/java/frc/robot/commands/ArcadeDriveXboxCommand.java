package frc.robot.commands;

import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.Robot;
import frc.robot.subsystems.Chassis;

public class ArcadeDriveXboxCommand extends Command{

    public ArcadeDriveXboxCommand() {
        requires(Robot.chassis);
    }

     // Called just before this Command runs the first time
    @Override
    protected void initialize() {
        Robot.chassis.stop();
    }

    // Called repeatedly when this Command is scheduled to run
    @Override
    protected void execute() {
        Robot.chassis.arcade(-Robot.oi.driver.getY(Hand.kLeft), Robot.oi.driver.getX(Hand.kRight));
    }

    // Make this return true when this Command no longer needs to run execute()
    @Override
    protected boolean isFinished() {
        return false;
    }

    // Called once after isFinished returns true
    @Override
    protected void end() {
        Robot.chassis.stop();
    }

    // Called when another command which requires one or more of the same
    // subsystems is scheduled to run
    @Override
    protected void interrupted() {
        Robot.chassis.stop();
    }

}