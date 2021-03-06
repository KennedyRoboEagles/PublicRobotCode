/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands.hatch;

import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.subsystems.HatchIntake;

public class CaptureHatchCommand extends Command {
  public CaptureHatchCommand() {
    // Use requires() here to declare subsystem dependencies
    // eg. requires(chassis);
    requires(HatchIntake.getInstance());

    this.setTimeout(1);
  }

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
    HatchIntake.getInstance().retract();
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    HatchIntake.getInstance().retract();
    SmartDashboard.putBoolean("Hatch", true);
  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    return false;
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
  }
}
