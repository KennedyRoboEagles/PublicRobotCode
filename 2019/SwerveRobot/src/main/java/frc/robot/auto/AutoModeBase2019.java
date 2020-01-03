package frc.robot.auto;

import com.team254.lib.auto.AutoModeBase;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.trajectory.timing.TimedState;

import edu.wpi.first.wpilibj.Timer;

import java.util.List;
import java.util.ArrayList;
import com.team254.lib.trajectory.Trajectory;
import frc.robot.trajectory.TrajectoryGenerator;

/**
 * An abstract class that is the basis of the robot's autonomous routines. This is implemented in auto modes (which are
 * routines that do actions).
 */
public abstract class AutoModeBase2019 extends AutoModeBase {
    protected static TrajectoryGenerator.TrajectorySet trajectories = TrajectoryGenerator.getInstance().getTrajectorySet();

    public List<Trajectory<TimedState<Pose2dWithCurvature>>> getPaths(){
        return new ArrayList<>();
    }

    protected double startTime = 0.0;
    protected double currentTime(){
        return Timer.getFPGATimestamp() - startTime;
    }

}
