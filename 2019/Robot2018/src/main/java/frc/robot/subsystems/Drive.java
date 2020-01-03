/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.subsystems;

import edu.wpi.first.wpilibj.Talon;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.drive.MecanumDrive;
import frc.robot.RobotMap;
import frc.robot.commands.TeleopDriveCommand;

/**
 * Add your docs here.
 */
public class Drive extends Subsystem {
  // Put methods for controlling this subsystem
  // here. Call these from Commands.

  private final Talon frontLeft_;
  private final Talon frontRight_;
  private final Talon backLeft_;
  private final Talon backRight_;

  private final MecanumDrive drive_;

  public Drive() {
    // Constructor
    frontLeft_ = new Talon(RobotMap.kDriveFrontLeft);
    frontRight_ = new Talon(RobotMap.kDrIveFrontRight);
    backLeft_ = new Talon(RobotMap.kDriveBackLeft);
    backRight_ = new Talon(RobotMap.kDriveBackRight);

    drive_ = new MecanumDrive(
      frontLeft_, 
      backLeft_, 
      frontRight_, 
      backRight_
    );

    drive_.setSafetyEnabled(false);
  }

  @Override
  public void initDefaultCommand() {
    // Set the default command for a subsystem here.
    // setDefaultCommand(new MySpecialCommand());
    setDefaultCommand(new TeleopDriveCommand());
  }

  // Positive X is move forward
  // Positive Y is move right
  // Postive Rotate is clockwise
  public void move(double xForward, double yStrafe, double rotate) {
    drive_.driveCartesian(yStrafe, xForward, rotate);
  }

  public void stop() {
    drive_.driveCartesian(0, 0, 0);
  }

}
