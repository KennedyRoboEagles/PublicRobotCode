package frc.robot.auto.modes;

import java.util.Arrays;
import java.util.List;

import com.team254.lib.auto.AutoModeEndedException;
import com.team254.lib.auto.actions.WaitAction;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.trajectory.Trajectory;
import com.team254.lib.trajectory.timing.TimedState;

import edu.wpi.first.wpilibj.Timer;
import frc.robot.auto.AutoModeBase2019;
import frc.robot.auto.actions.ResetPoseAction;
import frc.robot.auto.actions.SetTrajectoryAction;
import frc.robot.auto.actions.WaitToFinishPathAction;

public class FarCloseBallMode extends AutoModeBase2019 {
//	Superstructure s;
    
    final boolean left;
    final double directionFactor;

    @Override
    public List<Trajectory<TimedState<Pose2dWithCurvature>>> getPaths() {
        return Arrays.asList(trajectories.startToFarHatch.get(left), trajectories.farHatchToHumanLoader.get(left), 
            trajectories.humanLoaderToCloseHatch.get(left), trajectories.closeHatchToBall.get(left),
            trajectories.ballToRocketPort.get(left));
    }

	public FarCloseBallMode(boolean left) {
//        s = Superstructure.getInstance();
        this.left = left;
        directionFactor = left ? -1.0 : 1.0;
    }

    @Override
    protected void routine() throws AutoModeEndedException {
        super.startTime = Timer.getFPGATimestamp();

        runAction(new ResetPoseAction(left));
        runAction(new SetTrajectoryAction(trajectories.startToFarHatch.get(left), 150.0 *directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());
        runAction(new WaitAction(0.5));
        runAction(new SetTrajectoryAction(trajectories.farHatchToHumanLoader.get(left), 180.0 * directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());
        runAction(new WaitAction(0.5));
        runAction(new SetTrajectoryAction(trajectories.humanLoaderToCloseHatch.get(left), 150.0 * directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());
        runAction(new WaitAction(0.5));
        runAction(new SetTrajectoryAction(trajectories.closeHatchToBall.get(left), 45.0 *directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());
        runAction(new WaitAction(0.5));
        runAction(new SetTrajectoryAction(trajectories.ballToRocketPort.get(left), 90.0 * directionFactor, 1.0));
        runAction(new WaitToFinishPathAction());

        System.out.println("Auto mode finished in " + currentTime() + " seconds");
	}
	
}