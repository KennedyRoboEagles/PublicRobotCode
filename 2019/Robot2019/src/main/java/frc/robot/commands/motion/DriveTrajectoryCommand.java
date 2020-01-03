/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.commands.motion;

import java.util.Arrays;
import java.util.List;

import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.trajectory.TimedView;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.TrajectoryIterator;
import com.team254.lib.trajectory.timing.CentripetalAccelerationConstraint;
import com.team254.lib.trajectory.timing.TimedState;
import com.team254.lib.trajectory.timing.TimingConstraint;

import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.command.Command;
import frc.robot.RobotState;
import frc.robot.paths.TrajectoryGenerator;
import frc.robot.subsystems.Drive;

/**
 * An example command.  You can replace me with your own command.
 */
@Deprecated
public class DriveTrajectoryCommand extends Command {
  private final Drive drive_ = Drive.getInstance();
  private final RobotState robotState_ = RobotState.getInstance();

  private final Trajectory<TimedState<Pose2dWithCurvature>> trajectory_;
  TrajectoryIterator<TimedState<Pose2dWithCurvature>> trajectoryIterator_;
  private final boolean resetPose_;

  public DriveTrajectoryCommand(List<Pose2d> waypoints, boolean resetPose) {
     this(TrajectoryGenerator.getInstance().generateTrajectory(
      false, 
      waypoints, 
      Arrays.asList(new CentripetalAccelerationConstraint(TrajectoryGenerator.kMaxCentripetalAccel)), 
      TrajectoryGenerator.kMaxVelocity, 
      TrajectoryGenerator.kMaxAccel, 
      TrajectoryGenerator.kMaxVoltage
      ), resetPose);
  }  
  
  public DriveTrajectoryCommand(Trajectory<TimedState<Pose2dWithCurvature>> trajectory) {
    this(trajectory, false);
  }

  public DriveTrajectoryCommand(Trajectory<TimedState<Pose2dWithCurvature>> trajectory, boolean resetPose) {
    // Use requires() here to declare subsystem dependencies
    requires(drive_);
    trajectoryIterator_ = null;
    trajectory_ = trajectory;
    resetPose_ = resetPose;
  }

  // Called just before this Command runs the first time
  @Override
  protected void initialize() {
    drive_.setBrakeMode(true);
    trajectoryIterator_ =  new TrajectoryIterator<>(new TimedView<>(trajectory_));
    System.out.println("Starting trajectory! (length=" + trajectoryIterator_.getRemainingProgress() + ")");
    if (resetPose_) {
      System.out.println("Resetting sensors");
      drive_.zeroSensors();

      System.out.println("Resetting pose");
      robotState_.reset(Timer.getFPGATimestamp(), trajectoryIterator_.getState().state().getPose());
    }
    drive_.setTrajectory(trajectoryIterator_);
  }

  // Called repeatedly when this Command is scheduled to run
  @Override
  protected void execute() {
    System.out.println("Remaining Progress " + trajectoryIterator_.getRemainingProgress());
  }

  // Make this return true when this Command no longer needs to run execute()
  @Override
  protected boolean isFinished() {
    if (drive_.isDoneWithTrajectory()) {
      System.out.println("Trajectory finished");
      return true;
    }

    return false;
  }

  // Called once after isFinished returns true
  @Override
  protected void end() {
    drive_.stop();
    // Clear exisiting trajectory
    // drive_.setTrajectory(null);
  }

  // Called when another command which requires one or more of the same
  // subsystems is scheduled to run
  @Override
  protected void interrupted() {
    this.end();
  }
}
