package frc.robot.subsystems;

import com.kennedyrobotics.RobotFactory;
import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.subsystem.KennSubsystem;
import com.kennedyrobotics.swerve.ModuleOffsets;
import com.kennedyrobotics.swerve.signals.SwerveSignal;
import com.kennedyrobotics.swerve.signals.SwerveSignal.ControlOrientation;
import com.kennedyrobotics.swerve.kennedy.SwerveCommand;
import com.kennedyrobotics.swerve.kennedy.SwerveDriveHelper;
import com.kennedyrobotics.swerve.module.hardware.KennedyModule;

import com.kennedyrobotics.swerve.module.drive.DriveSparkMax;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMaxLowLevel;
import com.team254.lib.geometry.Rotation2d;

import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import edu.wpi.first.wpilibj.SerialPort.Port;
import frc.robot.commands.TeleopCommand;

import java.util.Arrays;
import java.util.List;

public class KennedyDrive extends KennSubsystem {

    public static class PeriodicIO {
        // INPUTS
        public Rotation2d gyro_heading = Rotation2d.identity();

        // OUTPUTS
        public SwerveCommand swerveCommand = new SwerveCommand();
    }

    // Constants
    public final double kWheelBaseLength = RobotFactory.getInstance().getConstant("wheelbase_length");
    public final double kTrackWidth = RobotFactory.getInstance().getConstant("track_width");;

    // Helpers
    private final RobotFactory factory_;
    private final Logger log = LoggerFactory.getLogger("Drive");
    private final SwerveDriveHelper helper_ = new SwerveDriveHelper(kWheelBaseLength, kTrackWidth);
    private final ModuleOffsets moduleOffsets_ = new ModuleOffsets();

    // Hardware
    private final AHRS imu_;
    private final KennedyModule frontLeft_;
    private final KennedyModule frontRight_;
    private final KennedyModule backLeft_;
    private final KennedyModule backRight_;
    private final List<KennedyModule> modules_;

    // Hardware States
    private PeriodicIO periodicIO_;
    private Rotation2d gyroOffset_ = Rotation2d.identity();
    private boolean debugControl_;

    public void setDebugControl(boolean value) { debugControl_ = value; }

    public KennedyDrive(RobotFactory factory) {
        factory_ = factory;

        /*
         * Hardware State 
         */
        periodicIO_ = new PeriodicIO();

        /*
         * IMU
         */
        // TODO: Add getAHRS method to RobotFactory and read what port the NavX is from Yaml
        imu_ = new AHRS(Port.kUSB);

        /*
         * PID Configuration 
         */
        double kP = factory_.getConstant("drive", "steer_kp");
        double kI = factory_.getConstant("drive", "steer_ki");
        double kD = factory_.getConstant("drive", "steer_kd");

        /*
         * Modules 
         */
        KennedyModule.Config frontLeft = KennedyModule.getDefaultConfig(
                kP, kI, kD,
                new ModuleOdometry.Config(
                        Constants.kWheelScrubFactors[ModuleID.FRONT_LEFT.id],
                        Constants.kXScrubFactor,
                        Constants.kYScrubFactor,
                        Constants.kSimulateReversedCarpet
                )
        );
        frontLeft.moduleOffset = moduleOffsets_.getOffset(
                factory.getConstant("drive", "front_left_id").intValue()
        );
        frontLeft_ = new KennedyModule(
            ModuleID.FRONT_LEFT,
            frontLeft, 
            factory_.getCtreMotor("drive", "front_left_steer"),
            new DriveSparkMax(factory_.getRevMotor("drive", "front_left_drive", CANSparkMaxLowLevel.MotorType.kBrushless))
        );

        KennedyModule.Config frontRight = KennedyModule.getDefaultConfig(
                kP, kI, kD,
                new ModuleOdometry.Config(
                        Constants.kWheelScrubFactors[ModuleID.FRONT_LEFT.id],
                        Constants.kXScrubFactor,
                        Constants.kYScrubFactor,
                        Constants.kSimulateReversedCarpet
                )
        );
        frontRight.moduleOffset = moduleOffsets_.getOffset(
                factory.getConstant("drive", "front_right_id").intValue()
        );
        frontRight_ = new KennedyModule(
            ModuleID.FRONT_RIGHT,
            frontRight, 
            factory_.getCtreMotor("drive", "front_right_steer"),
            new DriveSparkMax(factory_.getRevMotor("drive", "front_right_drive", CANSparkMaxLowLevel.MotorType.kBrushless))
        );

        KennedyModule.Config backLeft = KennedyModule.getDefaultConfig(
                kP, kI, kD,
                new ModuleOdometry.Config(
                        Constants.kWheelScrubFactors[ModuleID.FRONT_LEFT.id],
                        Constants.kXScrubFactor,
                        Constants.kYScrubFactor,
                        Constants.kSimulateReversedCarpet
                )
        );
        backLeft.moduleOffset = moduleOffsets_.getOffset(
                factory.getConstant("drive", "back_left_id").intValue()
        );
        backLeft_ = new KennedyModule(
            ModuleID.REAR_LEFT,
            backLeft,
            factory_.getCtreMotor("drive", "back_left_steer"),
            new DriveSparkMax(factory_.getRevMotor("drive", "back_left_drive", CANSparkMax.MotorType.kBrushless))
        );

        KennedyModule.Config backRight = KennedyModule.getDefaultConfig(
                kP, kI, kD,
                new ModuleOdometry.Config(
                        Constants.kWheelScrubFactors[ModuleID.FRONT_LEFT.id],
                        Constants.kXScrubFactor,
                        Constants.kYScrubFactor,
                        Constants.kSimulateReversedCarpet
                )
        );
        backRight.moduleOffset = moduleOffsets_.getOffset(
                factory.getConstant("drive", "back_right_id").intValue()
        );
        backRight_ = new KennedyModule(
            ModuleID.REAR_RIGHT,
            backRight, 
            factory_.getCtreMotor("drive", "back_right_steer"),
            new DriveSparkMax(factory_.getRevMotor("drive", "back_right_drive", CANSparkMaxLowLevel.MotorType.kBrushless))
        );

        modules_ = Arrays.asList(
            frontLeft_,
            frontRight_,
            backLeft_,
            backRight_
        );

        this.postConstruction();
    }

    @Override
    protected void initDefaultCommand() {
        setDefaultCommand(new TeleopCommand());
    }

    public void initialize() {
        modules_.forEach((m) -> m.initialize());
    }

    /**
     * Periodic function ran in main robot thread
     */
    @Override
    public void periodic() {
    }

    public void set(SwerveSignal signal) {
        log.trace("Command: " + signal);

        if (signal.orientation() == ControlOrientation.kFieldCentric) {
            signal.fieldOrient(this.getHeading());
        }

        periodicIO_.swerveCommand = helper_.inverseKinmatics(signal);

        // Pass along the swerve singal's brake setting
        periodicIO_.swerveCommand.setBrake(signal.brakeMode());

        log.trace("Move " +
                periodicIO_.swerveCommand.frontLeft.demand + ", " +
                periodicIO_.swerveCommand.frontRight.demand + ", " +
                periodicIO_.swerveCommand.backLeft.demand + ", " +
                periodicIO_.swerveCommand.backRight.demand
        );
    }

    @Override
    public void stop() {
        frontLeft_.stop();
        frontRight_.stop();
        backLeft_.stop();
        backRight_.stop();
    }


    public synchronized Rotation2d getHeading() {
        return  periodicIO_.gyro_heading;
    }

    public synchronized void setHeading(Rotation2d heading) {
        System.out.println("SET HEADING: " + heading.getDegrees());

        gyroOffset_ = heading.rotateBy(Rotation2d.fromDegrees(imu_.getFusedHeading()).inverse());
        System.out.println("Gyro offset: " + gyroOffset_.getDegrees());

       periodicIO_.gyro_heading = heading;
    }


    /*
     * Team 254 CheesySubsystem interface
     */

    @Override
    public synchronized void readPeriodicInputs() {
        periodicIO_.gyro_heading = Rotation2d.fromDegrees(imu_.getFusedHeading()).inverse().rotateBy(gyroOffset_.inverse());
        SmartDashboard.putNumber("Gyro Heading", getHeading().getDegrees());

        modules_.forEach((m) -> m.readPeriodicInputs());


        // Set module signals
        frontLeft_.sendSignal(periodicIO_.swerveCommand.frontLeft);
        frontRight_.sendSignal(periodicIO_.swerveCommand.frontRight);
        backLeft_.sendSignal(periodicIO_.swerveCommand.backLeft);
        backRight_.sendSignal(periodicIO_.swerveCommand.backRight);
    }

    @Override
    public synchronized void writePeriodicOutputs() {
        if (!debugControl_) {
            modules_.forEach((m) -> m.writePeriodicOutputs());
        }
    }

    @Override
    public void outputTelemetry() {
        modules_.forEach((m) -> m.outputTelemetry());
    }

    public List<KennedyModule> modules() {
        return modules_;
    }

}