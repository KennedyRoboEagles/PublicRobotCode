/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.auto.modes;

import java.util.Arrays;
import java.util.List;


import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.AutoModeEndedException;
import com.team254.lib.auto.actions.WaitAction;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.timing.TimedState;

import edu.wpi.first.wpilibj.Timer;
import frc.robot.Constants;
import frc.robot.RobotState;
import frc.robot.auto.AutoModeBase2019;
import frc.robot.auto.actions.*;

/**
 * 
 */
public class CloseMidShipMode extends AutoModeBase2019 {
//    Superstructure s;
    Swerve swerve;
    RobotState robotState;

    final boolean left;
    final double directionFactor;

    @Override
    public List<Trajectory<TimedState<Pose2dWithCurvature>>> getPaths() {
        return Arrays.asList(trajectories.startToCloseShip.get(left), trajectories.closeShipToHumanLoader.get(left),
            trajectories.humanLoaderToMidShip.get(left));
    }

	public CloseMidShipMode(boolean left) {
//        s = Superstructure.getInstance();
        swerve = Swerve.getInstance();
        robotState = RobotState.getInstance();
        this.left = left;
        directionFactor = left ? -1.0 : 1.0;
    }

    @Override
    protected void routine() throws AutoModeEndedException {
        super.startTime = Timer.getFPGATimestamp();

        System.out.println("Resting Pose");
        runAction(new ResetPoseAction(left ? new Pose2d(Constants.kRobotLeftStartingPose.getTranslation(), Rotation2d.fromDegrees(90.0)) : new Pose2d(Constants.kRobotRightStartingPose.getTranslation(), Rotation2d.fromDegrees(-90.0))));
//        DiskScorer.getInstance().conformToState(DiskScorer.State.GROUND_DETECTED);
        System.out.println("Setting Trajectory : startToCloseShip");
        runAction(new SetTrajectoryAction(trajectories.startToCloseShip.get(left), -90.0 * directionFactor, 1.0));
//        LimelightProcessor.getInstance().setPipeline(left ? Pipeline.RIGHTMOST : Pipeline.LEFTMOST);
//        runAction(new WaitToPassXCoordinateAction((96.0 + Constants.kRobotWidth)));
//        s.diskScoringState(20.0, true);
//        runAction(new WaitToPassXCoordinateAction(238.0));
//        runAction(new WaitForElevatorAction(19.6, true));
//        runAction(new WaitForVisionAction(2.0));
//        s.diskTrackingState(Constants.kElevatorLowHatchHeight, Rotation2d.fromDegrees(-90.0 * directionFactor), 42.0, new Translation2d(-4.0, Constants.kCurvedVisionYOffset), 30.0);
//        runAction(new WaitForSuperstructureAction());
        System.out.println("Starting wait for path completion");
        runAction(new WaitToFinishPathAction());
        System.out.println("Path Completed");
        System.out.println("Setting X coordinate");
        swerve.setXCoordinate(Constants.closeShipPosition.getTranslation().x());
//        if(swerve.getVisionTargetPosition().x() > (Constants.closeShipPosition.getTranslation().x() - 1.0)){
//            System.out.println("Alliance kept at: " + robotState.getAlliance());
//        }else if(robotState.onStandardCarpet()){
//            SmartDashboardInteractions.Alliance newAlliance = SmartDashboardInteractions.NONSTANDARD_CARPET_SIDE;
//            if(robotState.getAlliance() == newAlliance){
//                newAlliance = SmartDashboardInteractions.STANDARD_CARPET_SIDE;
//            }
//            robotState.setAlliance(newAlliance);
//            swerve.setCarpetDirection(robotState.onStandardCarpet());
//            System.out.println("Alliance set to: " + newAlliance);
//        }else{
//            System.out.println("Robot traveled too far, AND its on the nonstandard side");
//        }
        System.out.println("Starting wait");
        runAction(new WaitAction(0.25));
        System.out.println("Wait done");


        runAction(new SetTrajectoryAction(trajectories.closeShipToHumanLoader.get(left), -180.0 * directionFactor, 0.75));
        runAction(new WaitAction(0.5));
//        s.diskScoringState(12.4, false);
//        LimelightProcessor.getInstance().setPipeline(Pipeline.RIGHTMOST);
        runAction(new WaitToPassXCoordinateAction(96.0));
        if(left)
            runAction(new WaitForHeadingAction(160.0, 190.0));
        else
            runAction(new WaitForHeadingAction(-190.0, -160.0));
        runAction(new WaitForVisionAction(3.0));
//        s.humanLoaderTrackingState();
        runAction(new WaitForSuperstructureAction());
        swerve.setYCoordinate(directionFactor * -1.0 * Constants.humanLoaderPosition.getTranslation().y());
        swerve.setXCoordinate(Constants.kRobotHalfLength);
        //runAction(new WaitAction(0.25));


        runAction(new SetTrajectoryAction(trajectories.humanLoaderToMidShip.get(left), -90.0 * directionFactor, 0.75));
//        LimelightProcessor.getInstance().setPipeline(left ? Pipeline.LEFTMOST : Pipeline.RIGHTMOST);
        runAction(new WaitToPassXCoordinateAction((96.0 + Constants.kRobotWidth)));
        robotState.setXTarget(Constants.midShipPosition.getTranslation().x(), 8.0);
//        s.diskScoringState(20.0, false);
        //runAction(new WaitToPassXCoordinateAction(264.0));//282.55 267
        runAction(new WaitForElevatorAction(19.6, true));
        runAction(new WaitForVisionAction(2.0));
        runAction(new WaitForVisionPositionAction(Constants.midShipPosition.transformBy(Pose2d.fromTranslation(new Translation2d(-Constants.kRobotHalfLength - 4.0, 8.0))).getTranslation().x()));
//        s.diskTrackingState(Constants.kElevatorLowHatchHeight, Rotation2d.fromDegrees(-90.0 * directionFactor), 42.0, new Translation2d(-4.0, Constants.kCurvedVisionYOffset), 30.0);
        runAction(new WaitForSuperstructureAction());
        swerve.setXCoordinate(Constants.midShipPosition.getTranslation().x());
        robotState.enableXTarget(false);
        runAction(new WaitAction(0.25));

        //runAction(new SetTrajectoryAction(trajectories.closeShipToHumanLoader.get(left), -180.0 * directionFactor, 1.0));
        swerve.setRobotCentricTrajectory(new Translation2d(-36.0, 0.0), -90.0 * directionFactor);

        System.out.println("Auto mode finished in " + currentTime() + " seconds");
	}
	
}
