/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import java.util.Arrays;

import com.kennedyrobotics.drivers.RevDigit;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.loops.Looper;
import com.team254.lib.subsystems.SubsystemManager;
import com.team254.lib.util.CrashTracker;
import com.team254.lib.util.DriveSignal;

import org.opencv.core.Core;
import org.opencv.core.Mat;
import org.opencv.imgproc.Imgproc;

import edu.wpi.cscore.CvSink;
import edu.wpi.cscore.CvSource;
import edu.wpi.cscore.MjpegServer;
import edu.wpi.cscore.UsbCamera;
import edu.wpi.cscore.VideoMode;
import edu.wpi.first.cameraserver.CameraServer;
import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.TimedRobot;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.buttons.InternalButton;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.CommandGroup;
import edu.wpi.first.wpilibj.command.Scheduler;
import edu.wpi.first.wpilibj.command.WaitCommand;
import edu.wpi.first.wpilibj.smartdashboard.SendableChooser;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.commands.ExampleCommand;
import frc.robot.commands.intake.ControlIntakePivotCommand;
import frc.robot.subsystems.CargoIntake;
import frc.robot.subsystems.Drive;
import frc.robot.subsystems.HatchIntake;
import frc.robot.subsystems.IntakePivot;
import frc.robot.subsystems.Lift;
import frc.robot.subsystems.LiftDrive;
import frc.robot.subsystems.Pneumatics;
import frc.robot.subsystems.RobotStateEstimator;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the TimedRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the build.gradle file in the
 * project.
 */
public class Robot extends TimedRobot {
  // private class VisionRunner implements Runnable {
  //   @Override
  //   public void run() {
  //     // Get the UsbCamera from CameraServer
  //     UsbCamera camera = CameraServer.getInstance().startAutomaticCapture();
  //     // Set the resolution
  //     camera.setResolution(320, 240);
  //     camera.setFPS(15);
  //     // camera_.setVideoMode(VideoMode.PixelFormat.kMJPEG, 320, 240, 15);

  //     CvSink cvSink = CameraServer.getInstance().getVideo();

  //     CvSource outputStream = CameraServer.getInstance().putVideo("Rotated", 240, 320);

  //     Mat mat = new Mat();

  //     while (!Thread.interrupted()) {
  //        // Tell the CvSink to grab a frame from the camera and put it
  //       // in the source mat.  If there is an error notify the output.
  //       if (cvSink.grabFrame(mat) == 0) {
  //         // Send the output the error.
  //         outputStream.notifyError(cvSink.getError());
  //         // skip the rest of the current iteration
  //         continue;
  //       }

  //       Core.rotate(mat, mat, Core.ROTATE_90_COUNTERCLOCKWISE);

  //       outputStream.putFrame(mat);
  //     }
  //   }
  // }

  private class CargoRaiseThing extends CommandGroup {
      public CargoRaiseThing() {
        this.addSequential(new WaitCommand(0.25));
        this.addSequential(new ControlIntakePivotCommand(ControlIntakePivotCommand.Direction.kUp));
      }
  }

  private Looper enabledLooper_ = new Looper();
  private Looper disabledLooper_ = new Looper();

  private Command autoCommand_;
  private final RevDigit revDigit_ = new RevDigit();
  private final AutoSelection autoSelector_ = new AutoSelection(revDigit_);

  // private final Thread visionThread_ = new Thread(new VisionRunner());

  private InternalButton cargoRaiseButton;
  
  private boolean solenoidsInitialized_ = false;

  // TODO: Is ths needed?
  private final SubsystemManager subsystemManager_ = new SubsystemManager(
    Arrays.asList(
      RobotStateEstimator.getInstance(),
      Drive.getInstance()
    )
  );

  private UsbCamera camera_;
  private MjpegServer cameraServer_;

  private AnalogInput distanceSensor_;


  public Robot() {
    CrashTracker.logRobotConstruction();
  }

  /**
   * This function is run when the robot is first started up and should be
   * used for any initialization code.
   */
  @Override
  public void robotInit() {
    try {
      Pneumatics.getInstance().init();

      autoSelector_.init();
      // camera_ = CameraServer.getInstance().startAutomaticCapture();
      // camera_.setVideoMode(VideoMode.PixelFormat.kMJPEG, 320, 240, 15);
      // cameraServer_ = new MjpegServer("serve_USB Camera 0", Constants.kCameraStreamPort);
      // cameraServer_.setSource(camera_);


      // visionThread_.setDaemon(true);
      // visionThread_.start();

      subsystemManager_.registerEnabledLoops(enabledLooper_);
      subsystemManager_.registerDisabledLoops(disabledLooper_);

      cargoRaiseButton = new InternalButton();
      cargoRaiseButton.whenPressed(new ControlIntakePivotCommand(ControlIntakePivotCommand.Direction.kUp));
      // cargoRaiseButton.whenPressed(new CargoRaiseThing());

      distanceSensor_ = new  AnalogInput(2);

      LiftDrive.getInstance();
    } catch (Throwable t) {
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
    cargoRaiseButton.setPressed(CargoIntake.getInstance().isCargoPresentSecond());

    double distance = distanceSensor_.getAverageVoltage() * 40.3149606299;
    distance -= 14;
    SmartDashboard.putNumber("HAB Distance", distance);

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

      Drive.getInstance().zeroSensors();
      RobotState.getInstance().reset(Timer.getFPGATimestamp(), Pose2d.identity());

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
      outputToSmartDashboard();
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
    this.initSolendoids();
    SmartDashboard.putString("Match Cycle", "AUTONOMOUS");

    try {
      CrashTracker.logAutoInit();
      disabledLooper_.stop();

      RobotState.getInstance().reset(Timer.getFPGATimestamp(), Pose2d.identity());

      Drive.getInstance().zeroSensors();
      
      autoCommand_ = autoSelector_.selectedCmd();
      if(autoCommand_ != null) {
        autoCommand_.start();
      }

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

    outputToSmartDashboard();
    try {
      // Run WPI command scheduler
      Scheduler.getInstance().run();
    } catch (Throwable t) {
        CrashTracker.logThrowableCrash(t);
        throw t;
    }  }

  @Override
  public void teleopInit() {
    this.initSolendoids();
    SmartDashboard.putString("Match Cycle", "TELEOP");

    try {
      CrashTracker.logTeleopInit();
      disabledLooper_.stop();

      // This makes sure that the autonomous stops running when
      // teleop starts running. If you want the autonomous to
      // continue until interrupted by another command, remove
      // this line or comment it out.
		  if (autoCommand_ != null) {
  			autoCommand_.cancel();
	  	}

      RobotState.getInstance().reset(Timer.getFPGATimestamp(), Pose2d.identity());
      enabledLooper_.start();
      
      Drive.getInstance().setVelocity(DriveSignal.NEUTRAL, DriveSignal.NEUTRAL);
      Drive.getInstance().setOpenLoop(new DriveSignal(0.05, 0.05));
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

      outputToSmartDashboard();
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

          //mDrive.checkSystem();
          //mIntake.checkSystem();
          //mWrist.checkSystem();
          // mElevator.checkSystem();

      } catch (Throwable t) {
          CrashTracker.logThrowableCrash(t);
          throw t;
      }
  }

  public void outputToSmartDashboard() {
    RobotState.getInstance().outputToSmartDashboard();
    Drive.getInstance().outputTelemetry();
    // SmartDashboard.updateValues();
  }

  private void initSolendoids() {
    if (solenoidsInitialized_) return;
    solenoidsInitialized_ = true;

    Lift.getFrontInstance().retract();
    Lift.getBackInstance().retract();
    HatchIntake.getInstance().retract();
    IntakePivot.getInstance().up();
  }
}
