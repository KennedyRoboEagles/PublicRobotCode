package frc.robot;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;

import com.kennedyrobotics.drivers.RevDigit;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import com.team254.lib.trajectory.timing.CentripetalAccelerationConstraint;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.Preferences;
import edu.wpi.first.wpilibj.command.Command;
import edu.wpi.first.wpilibj.command.PrintCommand;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.commands.motion.TrajectoryCommand;
import frc.robot.paths.TrajectoryGenerator;
import jaci.pathfinder.Pathfinder;
import jaci.pathfinder.Waypoint;

public class AutoSelection implements Runnable {

    public static final String kPreferenceKey = "selected_auto";
    public static final String kSmartDashbboardKey = "Selected Auto";

    public enum Auto {
        kDefaultAuto("Default Auto", "Auto"),
        kTestAuto("Test auto", "Test"),
        kCharacterizeAuto("Char", "Char");

        public final String name;
        public final String displayName;
        private Auto(String name, String displayName) {
            this.name = name;
            this.displayName = displayName;
        }
    };

    private Logger log = LoggerFactory.getLogger("AutoSelection");

    private final RevDigit revDigit_;
    private final Map<Auto, Command> auto2cmd_ = new HashMap<Auto, Command>();
    private Auto selectedAuto_;
    private Thread workerThread_;

    public synchronized Auto selectedAuto() { return selectedAuto_; }
    public synchronized Command selectedCmd() { return auto2cmd_.get(selectedAuto_); }

    public AutoSelection(RevDigit revDigit) {
        revDigit_ = revDigit;
    }  

    /**
     * Initialize autoselction with Commands
     */
    public synchronized void init() {
        log.info("Starting initialization");
        // Populate commands
        auto2cmd_.put(Auto.kDefaultAuto, new PrintCommand("Running Auto!"));
        auto2cmd_.put(Auto.kTestAuto, new PrintCommand("Test command"));
        // auto2cmd_.put(Auto.kCharacterizeAuto, new CharacterizeDriveCommand());
    //     auto2cmd_.put(Auto.kCharacterizeAuto, 
    // new DriveTrajectoryCommand(
        // TrajectoryGenerator.getInstance().generateTrajectory(false, Arrays.asList(new Pose2d(Translation2d.identity(), Rotation2d.identity())),
        //     Arrays.asList(new CentripetalAccelerationConstraint(TrajectoryGenerator.kMaxCentripetalAccel), TrajectoryGenerator.kMaxVelocity, TrajectoryGenerator.kMaxAccel, TrajectoryGenerator.kMaxVoltage))));
        // Arrays.asList(new CentripetalAccelerationConstraint(TrajectoryGenerator.kMaxCentripetalAccel))
        // P;
        // auto2cmd_.put(Auto.kCharacterizeAuto, new DriveTrajectoryCommand(TrajectoryGenerator.getInstance().generateTrajectory(
        //     false,
        //     Arrays.asList(
        //             Pose2d.identity(), 
        //             // Pose2d.fromTranslation(new Translation2d(24.0, 0.0))
        //             // new Pose2d(new Translation2d(96.0, -48.0), Rotation2d.fromDegrees(-90.0)),
        //             new Pose2d(new Translation2d(48.0, -48.0), Rotation2d.fromDegrees(-90.0))
        //     ),
        //     Arrays.asList(new CentripetalAccelerationConstraint(80.0)),
        //     30.0, 30.0, 10.0),true));
        auto2cmd_.put(Auto.kCharacterizeAuto, new TrajectoryCommand(Arrays.asList(
            new Waypoint(0, 0, 0),
            new Waypoint(60, 0, 0)
        )));

        // Get stored auto value from the file system
        int autoIndex = Preferences.getInstance().getInt(kPreferenceKey, Auto.kDefaultAuto.ordinal());
        if (autoIndex >= Auto.values().length) {
            // Selected auto is out of range
            autoIndex = Auto.kDefaultAuto.ordinal();
        }
        setAuto(Auto.values()[autoIndex]);

        workerThread_ = new Thread(this);
        workerThread_.start();
        log.info("Initialization done");
    }

    /**
     * Worker thread to update Selected auto from display
     */
    @Override
    public void run() {
        log.info("Starting Worker thread");
        while (true) {
            this.tick();
            try {
                Thread.sleep(100);
            } catch (InterruptedException e) {
                System.err.println("AutoSlection Could not sleep");
            }
        }
    }

    /**
     * Worker thread tick
     */
    private synchronized void tick() {
        log.debug("Tick");
        if(revDigit_.getA()) {
            // Goto next auto
            this.nextAuto();
        } else if(revDigit_.getB()) {
            // Goto previous auto
            this.perviousAuto();
        } else {
            // Do nothing
        }

        // Update Display
        revDigit_.display(selectedAuto_.displayName);
    }

    /**
     * Advance to the next auto
     */
    private synchronized void nextAuto() {
        int next = (selectedAuto_.ordinal() + 1) % Auto.values().length;
        setAuto(Auto.values()[next]);
        log.info("Advance to next auto: {}", selectedAuto_.name());
    }

    /**
     * Advance to the previous auto
     */
    private synchronized void perviousAuto() {
        int next = selectedAuto_.ordinal() - 1;
        if (next < 0) {
            next = Auto.values().length - 1;
        }
        setAuto(Auto.values()[next]);
        log.info("Advance to pervious auto: {}", selectedAuto_.name());
    }

    /**
     * Update the currently selected auto
     * This will update the Prefernces and SmartDashboard key value 
     * @param auto
     */
    private synchronized void setAuto(Auto auto) {
        selectedAuto_ = auto;
        Preferences.getInstance().putInt(kPreferenceKey, selectedAuto_.ordinal());
        SmartDashboard.putString("Selected Auto", kSmartDashbboardKey);
    }
}