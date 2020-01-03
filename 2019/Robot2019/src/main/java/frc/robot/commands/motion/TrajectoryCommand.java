package frc.robot.commands.motion;

import java.util.List;

import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.team254.lib.util.DriveSignal;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.Notifier;
import edu.wpi.first.wpilibj.Preferences;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Robot;
import frc.robot.subsystems.Drive;
import jaci.pathfinder.Pathfinder;
import jaci.pathfinder.Trajectory;
import jaci.pathfinder.Waypoint;
import jaci.pathfinder.followers.DistanceFollower;
import jaci.pathfinder.modifiers.TankModifier;

public class TrajectoryCommand extends Command {
    private final Logger log = LoggerFactory.getLogger("TrajectoryCommand"); 

    private final Preferences preferences_ = Preferences.getInstance();
    private final Drive chassis_ = Drive.getInstance();
    private final TalonSRX left_ = chassis_.getLeft();
    private final TalonSRX right_ = chassis_.getRight();

    // NOTE: This is in inches
    private final double kDtMs = 20;
    private final double kDtSeconds = kDtMs / 1000.0;
    private final double kMaxVelocity = 30; // Inch/sec
    private final double kMaxAcceleration = 2*30; // Inch/sec^2
    private final double kMaxJerk = 5*30; // Inch/sec^3

    private final Trajectory leftTrajectory_;
    private final Trajectory rightTrajectory_;
    private double kTurnP = 0;
    private double headingError_;

    private final Trajectory.Config config_ = new Trajectory.Config(
        Trajectory.FitMethod.HERMITE_CUBIC, 
        Trajectory.Config.SAMPLES_LOW, 
        kDtSeconds,
        kMaxVelocity,
        kMaxAcceleration,
        kMaxJerk
    );

    private final DistanceFollower leftFollower_ = new DistanceFollower();
    private final DistanceFollower rightFollower_ = new DistanceFollower();
    private final Notifier notifier_ = new Notifier(() -> {
        headingError_ = Pathfinder.boundHalfDegrees(Pathfinder.r2d(leftFollower_.getHeading()) - chassis_.getHeading().getDegrees());
        double turn = headingError_ * kTurnP;
        double leftOutput = leftFollower_.calculate(chassis_.getLeftDistance());
        double rightOutput = rightFollower_.calculate(chassis_.getRightDistance());

        // left_.set(ControlMode.PercentOutput, leftOutput + turn);
        // right_.set(ControlMode.PercentOutput, rightOutput - turn);

        DriveSignal signal = new DriveSignal(leftOutput + turn, rightOutput - turn);
        chassis_.setOpenLoop(signal);
    });

    public TrajectoryCommand(List<Waypoint> points) {
        requires(chassis_);
        
        // TODO: There should be a way to pull trajectory points from a CSV file
        log.info("Starting trajectory generation");
        Waypoint[] array  = new Waypoint[points.size()];
        points.toArray(array);
        Trajectory trajectory = Pathfinder.generate(array, config_);

        // Wheelbase Width = 0.5m
        // TOOD make this a constant
        TankModifier modifier = new TankModifier(trajectory).modify(28.9);
        log.info("Done");

        // Do something with the new Trajectories...
        leftTrajectory_ = modifier.getLeftTrajectory();
        rightTrajectory_ = modifier.getRightTrajectory();

        // Check preferences
        if (!preferences_.containsKey("l_p")) {
            preferences_.putDouble("l_p", 0);
        }
        if (!preferences_.containsKey("l_i")) {
            preferences_.putDouble("l_i", 0);
        }
        if (!preferences_.containsKey("l_d")) {
            preferences_.putDouble("l_d", 0);
        }
        if (!preferences_.containsKey("l_v")) {
            preferences_.putDouble("l_v", 0);
        }
        if (!preferences_.containsKey("l_a")) {
            preferences_.putDouble("l_a", 0);
        }

        if (!preferences_.containsKey("r_p")) {
            preferences_.putDouble("r_p", 0);
        }
        if (!preferences_.containsKey("r_i")) {
            preferences_.putDouble("r_i", 0);
        }
        if (!preferences_.containsKey("r_d")) {
            preferences_.putDouble("r_d", 0);
        }
        if (!preferences_.containsKey("r_v")) {
            preferences_.putDouble("r_v", 0);
        }
        if (!preferences_.containsKey("r_a")) {
            preferences_.putDouble("r_a", 0);
        }

        if (!preferences_.containsKey("a_p")) {
            preferences_.putDouble("a_p", 0);
        }


        // Setup followers
        leftFollower_.configurePIDVA(0, 0, 0, 0, 0);
        rightFollower_.configurePIDVA(0, 0, 0, 0, 0);

        // Set trajectories
        leftFollower_.setTrajectory(leftTrajectory_);
        rightFollower_.setTrajectory(rightTrajectory_);
    }

    @Override
    protected void initialize() {
        // chassis_.setManual();
        log.info("Starting");
        chassis_.stop();
        chassis_.resetEncoders();
        chassis_.imu().zeroYaw();
        // Enabling break helps controlability  
        chassis_.setBrakeMode(true);

        // Pull PID/VA values from Robot preferences
        leftFollower_.configurePIDVA(
            preferences_.getDouble("l_p", 0),
            preferences_.getDouble("l_i", 0),
            preferences_.getDouble("l_d", 0),
            preferences_.getDouble("l_v", 0),
            preferences_.getDouble("l_a", 0)
        );
        rightFollower_.configurePIDVA(
            preferences_.getDouble("r_p", 0),
            preferences_.getDouble("r_i", 0),
            preferences_.getDouble("r_d", 0),
            preferences_.getDouble("r_v", 0),
            preferences_.getDouble("r_a", 0)
        );

        // Prepare followers
        leftFollower_.reset();
        rightFollower_.reset();
        notifier_.startPeriodic(kDtSeconds);
    }

    @Override
    protected void execute() {
        // chassis_.setManual();
        SmartDashboard.putNumber("heading_error", headingError_);
    }

    @Override
    protected boolean isFinished() {
        return leftFollower_.isFinished() && rightFollower_.isFinished();
    }

    @Override
    protected void end() {
        log.info("Done!");
        chassis_.stop();
        notifier_.stop();
    }

    @Override
    protected void interrupted() {
        this.end();
    }
}