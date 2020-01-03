/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */
public class RobotMap {
  // For example to map the left and right motors, you could define the
  // following variables to use with your drivetrain subsystem.
  // public static int leftMotor = 1;
  // public static int rightMotor = 2;

  // If you are using multiple modules, make sure to define both the port
  // number and the module. For example you with a rangefinder:
  // public static int rangefinderPort = 1;
  // public static int rangefinderModule = 1;

  /**
   * CAN IDs
   * (Note that if multiple talons are dedicated to a mechanism, any sensor are attached to the master) 
   */
  public static final int kLiftDriveTalonID = 13;
  // Drive
  public static final int kLeftDriveMasterId = 21;
  public static final int kRightDriveMasterId = 20;
  // Followers
  public static final int kLeftDriveFollowerId = 23;
  public static final int kRightDriveFollowerId = 22;


  /**
   * DIO
   */
  public static final int kFrontExtendSwitchChannel = 9;
  public static final int kFrontRetractSwitchChannel = 8;
  public static final int kBackExtendSwitchChannel = 7;
  public static final int kBackRetractSwitchChannel = 6;



  // Cargo Intake
  public static final int kCargoIntakeTalonId = 11;

  /**
   * DIO
   */
  public static final int kCargoDetectFirstChannel = 0;
  public static final int kCargoDetectSecondChannel = 1;

  /**
   * Analog
   */
  public static final int kPressureTransducerChannel = 3; 


  /*
   * PCM
   */
  public static final int kFrontExtendChannel = 5;
  public static final int kFrontRetractChannel = 4;

  public static final int kIntakeHatchForwardChannel = 3;
  public static final int kIntakeHatchReverseChannel = 2;


  public static final int kIntakePivotForwardChannel = 6;
  public static final int kIntakePivotReverseChannel = 7;

  public static final int kBackExtendChannel = 1;
  public static final int kBackRetractChannel = 0;
}
