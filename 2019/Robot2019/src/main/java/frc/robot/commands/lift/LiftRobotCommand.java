/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands.lift;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.Notifier;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.subsystems.Drive;
import frc.robot.subsystems.Lift;;

/**
 * An example command.  You can replace me with your own command.
 */
public class LiftRobotCommand extends Command {

  private static final double kTimeout = 20;

  private final Logger log = LoggerFactory.getLogger("LiftCmd");

  private final Lift front_ = Lift.getFrontInstance();
  private final Lift back_ = Lift.getBackInstance();
  private final Timer timer_= new Timer();

  public LiftRobotCommand() {
    // Use requires() here to declare subsystem dependencies
    requires(front_);
    requires(back_);
    SmartDashboard.putNumber("Lift Error Rate", 0);
  }

  // boolean state = false;
  // Notifier n_;

  double frontOffset_ = 0;
  double backOffset_ = 0;

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
    timer_.reset();
    timer_.start();
    Drive.getInstance().imu().reset();
    frontOffset_ = front_.getDistance();
    backOffset_ = back_.getDistance();

    laseError_ = 0;

  }

  private double laseError_ = 0;

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    double front = front_.getDistance();
    double back = back_.getDistance();
    front -= frontOffset_;
    back -= backOffset_;
    double delta  = front - back;

    final double kTollerance = 2;
    final double kDt = 20.0 / 1000.0;

    final double kStopFrontRate = 10;
    final double kStopBackRate = 10;

    double errorRate = delta / kDt;
 
    SmartDashboard.putNumber("Lift Error Rate", errorRate);


    if (errorRate < -10) {
      front_.extend();
      back_.stop();
    } else {
      if (delta < - kTollerance) {
        // Back is more extended than the front
        // Stop back
        front_.extend();
        back_.stop();
        log.info("Stopping Back");
      } else if (kTollerance < delta) {
        // Front is more extended than the back
        // Stop front
        front_.stop();
        back_.extend();
        log.info("Stopping Back");
      } else {
        // Raise normal
        log.info("Rasising");
        front_.extend();
        back_.extend();
      }
    }
  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    return timer_.hasPeriodPassed(kTimeout);
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
    front_.stop();
    back_.stop();
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
    this.end();
  }

  // @Deprecated
  // protected void executePitch() {
  //   double pitch = Drive.getInstance().imu().getPitch();

  //   pitch -= offset_;

  //   double kTollerance = 4;

  //   front_.extend();
  
  //   if (pitch < -kTollerance) {
  //     // Tilting forward
  //     // Stop back
  //     back_.stop();
  //     log.info("Stopping Back");
  //   } else {
  //     // Raise normal
  //     log.info("Rasising");
  //     back_.extend();
  //   }
  // }
  
}
