/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.OI;
import frc.robot.Robot;
import frc.robot.subsystems.Drive;

public class TeleopDriveCommand extends Command {

  private final Drive drive_ = Robot.m_drive;
  private final OI oi_ = Robot.m_oi;

  public TeleopDriveCommand() {
    // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    requires(Robot.m_drive);
  }

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    double xForward = oi_.getForward();
    double yStrafe = oi_.getStrafe();
    double rotate = oi_.getRotation();

    xForward = Math.copySign(xForward*xForward, xForward);
    yStrafe = Math.copySign(yStrafe*yStrafe, yStrafe);
    rotate = Math.copySign(rotate*rotate, rotate);

    SmartDashboard.putNumber("X", xForward);
    SmartDashboard.putNumber("Y", yStrafe);
    SmartDashboard.putNumber("Rotate", rotate);

    drive_.move(xForward, yStrafe, rotate);

  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    return false;
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
    drive_.stop();
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
    this.end();
  }
}
