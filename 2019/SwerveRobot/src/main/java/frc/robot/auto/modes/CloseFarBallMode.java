package frc.robot.auto.modes;

import java.util.Arrays;
import java.util.List;

import frc.robot.subsystems.Swerve;
import com.team254.lib.auto.AutoModeEndedException;
import com.team254.lib.auto.actions.WaitAction;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.timing.TimedState;

import edu.wpi.first.wpilibj.Timer;
import frc.robot.Constants;
import frc.robot.RobotState;
import frc.robot.auto.AutoModeBase2019;
import frc.robot.auto.actions.*;
import frc.robot.loops.LimelightProcessor;
import frc.robot.trajectory.TrajectoryGenerator;

public class CloseFarBallMode extends AutoModeBase2019 {
//    Superstructure s;

    final boolean left;
    final double directionFactor;

    @Override
    public List<Trajectory<TimedState<Pose2dWithCurvature>>> getPaths() {
        return Arrays.asList(trajectories.startToCloseHatch.get(left), trajectories.closeHatchToHumanLoader.get(left),
                trajectories.humanLoaderToFarHatch.get(left), trajectories.farHatchToCloseShip.get(left));
    }

	public CloseFarBallMode(boolean left) {
//        s = Superstructure.getInstance();
        this.left = left;
        directionFactor = left ? -1.0 : 1.0;
    }

    @Override
    protected void routine() throws AutoModeEndedException {
        super.startTime = Timer.getFPGATimestamp();

        runAction(new ResetPoseAction(left));
//        DiskScorer.getInstance().conformToState(DiskScorer.State.GROUND_DETECTED);
        runAction(new SetTrajectoryAction(trajectories.startToCloseHatch.get(left), 30.0 * directionFactor, 1.0));
//        LimelightProcessor.getInstance().setPipeline(left ? Pipeline.LEFTMOST : Pipeline.RIGHTMOST);
        runAction(new WaitToPassYCoordinateAction((46.25 + Constants.kRobotWidth) * directionFactor));
//        s.diskScoringState(Constants.kElevatorMidHatchHeight, true);
        runAction(new WaitForDistanceAction(left ? Constants.closeHatchPosition.getTranslation() : Constants.rightCloseHatchPosition.getTranslation(), /*56.0*/62.0));//102
        runAction(new WaitForElevatorAction(19.6, true));
        runAction(new WaitForVisionAction(3.0));
        if(left)
            runAction(new WaitForHeadingAction(-40.0, -25.0));
        else
            runAction(new WaitForHeadingAction(25.0, 40.0));
//        s.diskTrackingState(Constants.kElevatorMidHatchHeight, Rotation2d.fromDegrees(30.0 * directionFactor), Constants.kClosestVisionDistance, new Translation2d(-5.0, /*Constants.kCurvedVisionYOffset*/0.0), Constants.kDefaultVisionTrackingSpeed);
        runAction(new WaitForSuperstructureAction());
        runAction(new WaitAction(0.25));


        runAction(new SetTrajectoryAction(trajectories.closeHatchToHumanLoader.get(left), 180.0 * directionFactor, 0.75));
        runAction(new WaitAction(0.5));
//        s.diskScoringState(12.4, false);
        LimelightProcessor.getInstance().setPipeline(LimelightProcessor.Pipeline.RIGHTMOST);
        runAction(new WaitToPassXCoordinateAction(96.0));
        if(left)
            runAction(new WaitForHeadingAction(-190.0, -160.0));
        else
            runAction(new WaitForHeadingAction(160.0, 190.0));
        runAction(new WaitForVisionAction(3.0));
//        s.humanLoaderTrackingState();
        runAction(new WaitForSuperstructureAction());
        Swerve.getInstance().setXCoordinate(RobotState.getInstance().onStandardCarpet() ? Constants.kRobotHalfLength : Constants.kRobotHalfLength /*+ 6.0*/);
        Swerve.getInstance().setYCoordinate(directionFactor * -1.0 * Constants.humanLoaderPosition.getTranslation().y());//TODO test this


        runAction(new SetTrajectoryAction(trajectories.humanLoaderToFarHatch.get(left), 150.0 * directionFactor, 1.0));
//        LimelightProcessor.getInstance().setPipeline(left ? Pipeline.RIGHTMOST : Pipeline.LEFTMOST);
        runAction(new RemainingProgressAction(3.75));
//        s.diskScoringState(Constants.kElevatorMidHatchHeight, false);
        runAction(new RemainingProgressAction(1.25 - 0.25));
//        s.diskTrackingState(Constants.kElevatorMidHatchHeight, Rotation2d.fromDegrees(150.0 * directionFactor), Constants.kClosestVisionDistance, new Translation2d(-3.0, /*Constants.kCurvedVisionYOffset*/ 0.0), 30.0);
        runAction(new WaitForSuperstructureAction());
        //runAction(new WaitAction(0.25));

        Swerve.getInstance().setXCoordinate(TrajectoryGenerator.farHatchScoringPose.getTranslation().x());
        Swerve.getInstance().setYCoordinate(directionFactor * -1.0 * TrajectoryGenerator.farHatchScoringPose.getTranslation().y());
        runAction(new SetTrajectoryAction(trajectories.farHatchToCloseShip.get(left), 90.0 * directionFactor, 1.0));
        //Swerve.getInstance().setRobotCentricTrajectory(new Translation2d(-18.0, 0.0), Swerve.getInstance().getPose().getRotation().getUnboundedDegrees(), 36.0);
        runAction(new WaitAction(0.5));
//        s.diskScoringState(Constants.kElevatorLowHatchHeight, false);
        runAction(new WaitToFinishPathAction());
        /*runAction(new WaitAction(0.5));
        runAction(new SetTrajectoryAction(trajectories.ballToRocketPort.get(left), 90.0 * directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());*/

        System.out.println("Auto mode finished in " + currentTime() + " seconds");
	}
	
}