/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import com.kennedyrobotics.RobotFactory;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import com.kennedyrobotics.subsystem.SubsystemManager;
import com.kennedyrobotics.util.JoystickWarningHelper;
import com.team254.ConstantUtil;

import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.loops.Looper;
import com.team254.lib.util.CrashTracker;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.subsystems.KennedyDrive;
import frc.robot.subsystems.ExampleSubsystem;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the TimedRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.gradle file in the
 * project.
 */
public class Robot extends TimedRobot {
  public static ExampleSubsystem m_subsystem;
  public static KennedyDrive m_drive;
//  public static Leds m_leds;
  public static OI m_oi;

  private SubsystemManager subsystemManager_;
  private Looper enabledLooper_ = new Looper();
  private Looper disabledLooper_ = new Looper();

  Robot() {
    CrashTracker.logRobotConstruction();

  }

  /**
   * This function is run when the robot is first started up and should be
   * used for any initialization code.
   */
  @Override
  public void robotInit() {
    try {
      CrashTracker.logRobotInit();

      // Disable Joystick warning
      JoystickWarningHelper.disableWarning();

      // Robot factory initialization
      Map<String, String> mac2robot = new HashMap<>();
      mac2robot.put("00-80-2F-17-C3-4F", "testbench");
      mac2robot.put("00-80-2F-17-F8-26", "swervebot");
      String macAddress = ConstantUtil.getMACAddress();
      DriverStation.reportError("MAC: " + macAddress, false);

      String robotName = mac2robot.get(macAddress);
      if (robotName == null) {
        DriverStation.reportError("ROBOT_NAME env variable not set", false);
        robotName = "swervebot";
      }
      DriverStation.reportError("ROBOT_NAME is " + robotName, false);
      RobotFactory.initialize(robotName);

      // Subsystem initialization
      m_subsystem = new ExampleSubsystem();
      m_drive = new KennedyDrive(RobotFactory.getInstance());
//      m_leds = new Leds(RobotFactory.getInstance());

      subsystemManager_ = new SubsystemManager(
              Arrays.asList(
                      m_drive
//                      m_leds
              )
      );

      subsystemManager_.registerDisabledLoops(disabledLooper_);
      subsystemManager_.registerEnabledLoops(enabledLooper_);

      m_oi = new OI();

      m_drive.initialize();
    } catch(Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  /**
   * This function is called every robot packet, no matter the mode. Use
   * this for items like diagnostics that you want ran during disabled,
   * autonomous, teleoperated and test.
   *
   * <p>This runs after the mode specific periodic functions, but before
   * LiveWindow and SmartDashboard integrated updating.
   */
  @Override
  public void robotPeriodic() {
    subsystemManager_.outputToSmartDashboard();

    SmartDashboard.putNumber("Memory Free", Runtime.getRuntime().freeMemory());
    SmartDashboard.putNumber("Memory Total", Runtime.getRuntime().totalMemory());
    SmartDashboard.putNumber("Memory Max", Runtime.getRuntime().maxMemory());

    SmartDashboard.putNumber("x-left", m_oi.controller.getX(Hand.kLeft));
    SmartDashboard.putNumber("x-right", m_oi.controller.getX(Hand.kRight));
    SmartDashboard.putNumber("y-left", m_oi.controller.getY(Hand.kLeft));
    SmartDashboard.putNumber("y-right", m_oi.controller.getY(Hand.kRight));
  }

  /**
   * This function is called once each time the robot enters Disabled mode.
   * You can use it to reset any subsystem information you want to clear when
   * the robot is disabled.
   */
  @Override
  public void disabledInit() {
    SmartDashboard.putString("Match Cycle", "DISABLED");

    try {
      CrashTracker.logDisabledInit();
      enabledLooper_.stop();
      disabledLooper_.start();

    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  @Override
  public void disabledPeriodic() {
    SmartDashboard.putString("Match Cycle", "DISABLED");

    try {
      // Run WPI command scheduler
      Scheduler.getInstance().run();
    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  /**
   * This autonomous (along with the chooser code above) shows how to select
   * between different autonomous modes using the dashboard. The sendable
   * chooser code works with the Java SmartDashboard. If you prefer the
   * LabVIEW Dashboard, remove all of the chooser code and uncomment the
   * getString code to get the auto name from the text box below the Gyro
   *
   * <p>You can add additional auto modes by adding additional commands to the
   * chooser code above (like the commented example) or additional comparisons
   * to the switch structure below with additional strings & commands.
   */
  @Override
  public void autonomousInit() {

    SmartDashboard.putString("Match Cycle", "AUTONOMOUS");

    try {
      CrashTracker.logAutoInit();
      disabledLooper_.stop();

      m_drive.initialize();

//      autoCommand_ = autoSelector_.selectedCmd();
//      if(autoCommand_ != null) {
//        autoCommand_.start();
//      }


      enabledLooper_.start();
    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  /**
   * This function is called periodically during autonomous.
   */
  @Override
  public void autonomousPeriodic() {
    SmartDashboard.putString("Match Cycle", "AUTONOMOUS");

    try {
      // Run WPI command scheduler
      Scheduler.getInstance().run();
    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  @Override
  public void teleopInit() {

    SmartDashboard.putString("Match Cycle", "TELEOP");


    // This makes sure that the autonomous stops running when
    // teleop starts running. If you want the autonomous to
    // continue until interrupted by another command, remove
    // this line or comment it out.
    try {
      CrashTracker.logTeleopInit();
      disabledLooper_.stop();
      enabledLooper_.start();

      m_drive.initialize();

      m_drive.setHeading(Rotation2d.identity());

      // This makes sure that the autonomous stops running when
      // teleop starts running. If you want the autonomous to
      // continue until interrupted by another command, remove
      // this line or comment it out.
//      if (autoCommand_ != null) {
//        autoCommand_.cancel();
//      }
    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  /**
   * This function is called periodically during operator control.
   */
  @Override
  public void teleopPeriodic() {
    SmartDashboard.putString("Match Cycle", "TELEOP");

    try {
      // Run WPI command scheduler
      Scheduler.getInstance().run();
    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }

  /**
   * This function is called periodically during test mode.
   */
  @Override
  public void testPeriodic() {
    SmartDashboard.putString("Match Cycle", "TEST");

    try {
      System.out.println("Starting check systems.");

      disabledLooper_.stop();
      enabledLooper_.stop();

    } catch (Throwable t) {
      CrashTracker.logThrowableCrash(t);
      throw t;
    }
  }
}
