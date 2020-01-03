package frc.robot.subsystems;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.ControlMode;
import com.ctre.phoenix.motorcontrol.DemandType;
import com.ctre.phoenix.motorcontrol.FeedbackDevice;
import com.ctre.phoenix.motorcontrol.InvertType;
import com.ctre.phoenix.motorcontrol.NeutralMode;
import com.ctre.phoenix.motorcontrol.StatusFrameEnhanced;
import com.ctre.phoenix.motorcontrol.VelocityMeasPeriod;
import com.ctre.phoenix.motorcontrol.can.BaseMotorController;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.ctre.phoenix.motorcontrol.can.VictorSPX;
import com.kauailabs.navx.frc.AHRS;
import com.kennedyrobotics.drivers.VictorSPXFactory;
import com.team254.lib.drivers.TalonSRXFactory;
import com.team254.lib.geometry.Pose2d;
import com.team254.lib.geometry.Pose2dWithCurvature;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.loops.ILooper;
import com.team254.lib.loops.Loop;
import com.team254.lib.subsystems.Subsystem;
import com.team254.lib.trajectory.TrajectoryIterator;
import com.team254.lib.trajectory.timing.TimedState;
import com.team254.lib.util.DriveSignal;
import com.team254.lib.util.ReflectingCSVWriter;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.SerialPort.Port;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;
import frc.robot.RobotMap;
import frc.robot.RobotState;
import frc.robot.commands.TeleopCommand;
import frc.robot.planners.DriveMotionPlanner;

public class Drive extends edu.wpi.first.wpilibj.command.Subsystem implements Subsystem {

    // The robot drivetrain's various states.
    public enum DriveControlState {
        OPEN_LOOP, // open loop voltage control
        PATH_FOLLOWING, // velocity PID control
        MANUAL, // Allow outside user to manage motor controllers
    }

    public static class PeriodicIO {
        // INPUTS
        public int left_position_ticks;
        public int right_position_ticks;
        public double left_distance;
        public double right_distance;
        public int left_velocity_ticks_per_100ms;
        public int right_velocity_ticks_per_100ms;
        public Rotation2d gyro_heading = Rotation2d.identity();
        public Pose2d error = Pose2d.identity();

        // OUTPUTS
        public double left_demand;
        public double right_demand;
        public double left_accel;
        public double right_accel;
        public double left_feedforward;
        public double right_feedforward;
        public TimedState<Pose2dWithCurvature> path_setpoint = new TimedState<Pose2dWithCurvature>(Pose2dWithCurvature.identity());
    }

    private static final int kControlSlot = 0;
    public static final double kDriveEncoderPPR = 120 * 4;

    private static Drive instance_ = new Drive();
    public static Drive getInstance() { return instance_; }

    // Hardware
    private final AHRS imu_;
    private final TalonSRX leftMaster_;
    private final VictorSPX leftFollower_;
    private final TalonSRX rightMaster_;
    private final VictorSPX rightFollower_;

    // Control states
    private DriveControlState driveControlState_;

    // Hardware states
    private PeriodicIO periodicIO_;
    private boolean isBrakeMode_;
    private ReflectingCSVWriter<PeriodicIO>csvWriter_ = null;
    private DriveMotionPlanner motionPlanner_;
    private Rotation2d gyroOffset_ = Rotation2d.identity();
    private boolean overrideTrajectory_ = false;

    private final Loop loop_ = new Loop() {

        @Override
        public void onStart(double timestamp) {
            synchronized(Drive.this) {
                setOpenLoop(new DriveSignal(0.05, 0.05));
                setBrakeMode(false);
                // startLogging();
            }
        }

        @Override
        public void onLoop(double timestamp) {
            synchronized(Drive.this) {
                switch (driveControlState_) {
                    case OPEN_LOOP:
                        break;
                    case PATH_FOLLOWING:
                        updatePathFollower();
                        break;
                    case MANUAL:
                        break;
                    default:
                        System.out.println("Unexpected drive control state: " +driveControlState_);
                        break;
                }
            }
        }

        @Override
        public void onStop(double timestamp) {
            stop();
            stopLogging();
        }

    };

    public TalonSRX getLeft() {
        return rightMaster_;
    }

    public TalonSRX getRight() {
        return leftMaster_;
    }

    public AHRS imu() {
        return imu_;
    }

    public Drive() {
       periodicIO_ = new PeriodicIO();

        // Start all Talons in open loop mode.
        leftMaster_ = TalonSRXFactory.createDefaultTalon(RobotMap.kLeftDriveMasterId);
        configureMaster(leftMaster_, true);
        // leftFollower_ = VictorSPXFactory.createPermanentSlaveTalon(RobotMap.kLeftDriveFollowerId, RobotMap.kLeftDriveMasterId);
        leftFollower_ = new VictorSPX(RobotMap.kLeftDriveFollowerId);
        leftFollower_.follow(leftMaster_);
        configureSlave(leftFollower_, true);


        rightMaster_ = TalonSRXFactory.createDefaultTalon(RobotMap.kRightDriveMasterId);
        configureMaster(rightMaster_, false);
        // rightFollower_ =  VictorSPXFactory.createPermanentSlaveTalon(RobotMap.kRightDriveFollowerId, RobotMap.kRightDriveMasterId);
        rightFollower_ = new VictorSPX(RobotMap.kRightDriveFollowerId);
        rightFollower_.follow(rightMaster_);
        configureSlave(rightFollower_, false);

        reloadGains();
        imu_ = new AHRS(Port.kUSB);

        setOpenLoop(DriveSignal.NEUTRAL);

        // Force a CAN message across.
        isBrakeMode_ = true;
        setBrakeMode(false);

        motionPlanner_ = new DriveMotionPlanner();
    }

    @Override
    protected void initDefaultCommand() {
        setDefaultCommand(new TeleopCommand());
    }

    /**
     * Ran in the main loop
     */
    @Override
    public void periodic() {
        SmartDashboard.putNumber("Pitch", imu_.getPitch());

        SmartDashboard.putString("Drive State", driveControlState_.toString());
        SmartDashboard.putNumber("Drive x err", periodicIO_.error.getTranslation().x());

        SmartDashboard.putNumber("Left Voltage", leftMaster_.getMotorOutputVoltage());
        SmartDashboard.putNumber("Right Voltage", rightMaster_.getMotorOutputVoltage());
    }

    private void configureMaster(TalonSRX talon, boolean left) {
        talon.setStatusFramePeriod(StatusFrameEnhanced.Status_3_Quadrature, 5, 100);
        final ErrorCode sensorPresent = talon.configSelectedFeedbackSensor(FeedbackDevice
                .QuadEncoder, 0, 100); //primary closed-loop, 100 ms timeout
        if (sensorPresent != ErrorCode.OK) {
            DriverStation.reportError("Could not detect " + (left ? "left" : "right") + " encoder: " + sensorPresent, false);
        }
        talon.setInverted(!left);
        talon.setSensorPhase(true);
        talon.enableVoltageCompensation(true);
        talon.configVoltageCompSaturation(12.0, Constants.kLongCANTimeoutMs);
        talon.configVelocityMeasurementPeriod(VelocityMeasPeriod.Period_50Ms, Constants.kLongCANTimeoutMs);
        talon.configVelocityMeasurementWindow(1, Constants.kLongCANTimeoutMs);
        talon.configClosedloopRamp(Constants.kDriveVoltageRampRate, Constants.kLongCANTimeoutMs);
        talon.configNeutralDeadband(0.04, 0);
    }

    private void configureSlave(BaseMotorController talon, boolean left) {
        talon.setInverted(InvertType.FollowMaster);
    }

    @Override
    public void registerEnabledLoops(ILooper in) {
        in.register(loop_);
    }

    /**
     * Configure talons for open loop control
     */
    public synchronized void setOpenLoop(DriveSignal signal) {
        if (driveControlState_ != DriveControlState.OPEN_LOOP) {
            setBrakeMode(false);

            System.out.println("Switching to open loop");
            System.out.println(signal);
            driveControlState_ = DriveControlState.OPEN_LOOP;
            leftMaster_.configNeutralDeadband(0.04, 0);
            rightMaster_.configNeutralDeadband(0.04, 0);
        }
       periodicIO_.left_demand = signal.getLeft();
       periodicIO_.right_demand = signal.getRight();
       periodicIO_.left_feedforward = 0.0;
       periodicIO_.right_feedforward = 0.0;
    }

     /**
     * Configures talons for velocity control
     */
    public synchronized void setVelocity(DriveSignal signal, DriveSignal feedforward) {
        if (driveControlState_ != DriveControlState.PATH_FOLLOWING) {
            // We entered a velocity control state.
            setBrakeMode(true);
            leftMaster_.selectProfileSlot(kControlSlot, 0);
            rightMaster_.selectProfileSlot(kControlSlot, 0);
            leftMaster_.configNeutralDeadband(0.0, 0);
            rightMaster_.configNeutralDeadband(0.0, 0);

            driveControlState_ = DriveControlState.PATH_FOLLOWING;
        }
       periodicIO_.left_demand = signal.getLeft();
       periodicIO_.right_demand = signal.getRight();
       periodicIO_.left_feedforward = feedforward.getLeft();
       periodicIO_.right_feedforward = feedforward.getRight();
    }

    public synchronized void setManual() {
        if (driveControlState_ != DriveControlState.MANUAL) {
            setBrakeMode(false);

            System.out.println("Switching to manual control");
            driveControlState_ = DriveControlState.MANUAL;
            leftMaster_.configNeutralDeadband(0.04, 0);
            rightMaster_.configNeutralDeadband(0.04, 0);
        }
    }

    public synchronized void setTrajectory(TrajectoryIterator<TimedState<Pose2dWithCurvature>> trajectory) {
        if (motionPlanner_ != null) {
           overrideTrajectory_ = false;
           motionPlanner_.reset();
           motionPlanner_.setTrajectory(trajectory);
           driveControlState_ = DriveControlState.PATH_FOLLOWING;
        }
    }

    public boolean isDoneWithTrajectory() {
        if (motionPlanner_ == null || driveControlState_ != DriveControlState.PATH_FOLLOWING) {
            return false;
        }
        return motionPlanner_.isDone() || overrideTrajectory_;
    }

    public boolean isBrakeMode() {
        return isBrakeMode_;
    }

    public synchronized void setBrakeMode(boolean on) {
        if (isBrakeMode_ != on) {
           isBrakeMode_ = on;
            NeutralMode mode = on ? NeutralMode.Brake : NeutralMode.Coast;
            rightMaster_.setNeutralMode(mode);
            rightFollower_.setNeutralMode(mode);

            leftMaster_.setNeutralMode(mode);
            leftFollower_.setNeutralMode(mode);
        }
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

    @Override
    public synchronized void stop() {
        setOpenLoop(DriveSignal.NEUTRAL);
    }

    @Override
    public boolean checkSystem() {
        return false;
    }

    @Override
    public void outputTelemetry() {
        //        periodicIO_.left_demand = signal.getLeft();
        //periodicIO_.right_demand = signal.getRight();
        //periodicIO_.left_feedforward = feedforward.getLeft();
        //periodicIO_.right_feedforward = feedforward.getRight();
        SmartDashboard.putNumber("Left Demand",periodicIO_.left_demand);
        SmartDashboard.putNumber("Left Feedforward",periodicIO_.left_feedforward);
        SmartDashboard.putNumber("Right Demand",periodicIO_.right_demand);
        SmartDashboard.putNumber("Right Feedforward",periodicIO_.right_feedforward);

        SmartDashboard.putNumber("Right Drive Distance",periodicIO_.right_distance);
        SmartDashboard.putNumber("Right Drive Ticks",periodicIO_.right_position_ticks);
        SmartDashboard.putNumber("Left Drive Ticks",periodicIO_.left_position_ticks);
        SmartDashboard.putNumber("Left Drive Distance",periodicIO_.left_distance);
        SmartDashboard.putNumber("Right Linear Velocity", getRightLinearVelocity());
        SmartDashboard.putNumber("Left Linear Velocity", getLeftLinearVelocity());

        SmartDashboard.putNumber("x err",periodicIO_.error.getTranslation().x());
        SmartDashboard.putNumber("y err",periodicIO_.error.getTranslation().y());
        SmartDashboard.putNumber("theta err",periodicIO_.error.getRotation().getDegrees());
        if (getHeading() != null) {
            SmartDashboard.putNumber("Gyro Heading", getHeading().getDegrees());
        }
        if (csvWriter_ != null) {
           csvWriter_.write();
        }
    }

    public synchronized void resetEncoders() {
        leftMaster_.setSelectedSensorPosition(0, 0, 0);
        rightMaster_.setSelectedSensorPosition(0, 0, 0);
       periodicIO_ = new PeriodicIO();
    }

    @Override
    public void zeroSensors() {
        setHeading(Rotation2d.identity());
        resetEncoders();
    }

    public double getLeftEncoderRotations() {
        return  periodicIO_.left_position_ticks / kDriveEncoderPPR;
    }

    public double getRightEncoderRotations() {
        return  periodicIO_.right_position_ticks / kDriveEncoderPPR;
    }

    public double getLeftDistance() {
        return periodicIO_.left_distance;
    }

    public double getRightDistance() {
        return periodicIO_.right_distance;
    } 

    public double getLeftEncoderDistance() {
        return rotationsToInches(getLeftEncoderRotations());
    }

    public double getRightEncoderDistance() {
        return rotationsToInches(getRightEncoderRotations());
    }

    public double getRightVelocityNativeUnits() {
        return  periodicIO_.right_velocity_ticks_per_100ms;
    }

    public double getRightLinearVelocity() {
        return rotationsToInches(getRightVelocityNativeUnits() * 10.0 / kDriveEncoderPPR);
    }

    public double getLeftVelocityNativeUnits() {
        return  periodicIO_.left_velocity_ticks_per_100ms;
    }

    public double getLeftLinearVelocity() {
        return rotationsToInches(getLeftVelocityNativeUnits() * 10.0 / kDriveEncoderPPR);
    }

    public double getLinearVelocity() {
        return (getLeftLinearVelocity() + getRightLinearVelocity()) / 2.0;
    }

    public double getAngularVelocity() {
        return (getRightLinearVelocity() - getLeftLinearVelocity()) / Constants.kDriveWheelTrackWidthInches;
    }

    public void overrideTrajectory(boolean value) {
       overrideTrajectory_ = value;
    }

    private void updatePathFollower() {
        if (driveControlState_ == DriveControlState.PATH_FOLLOWING) {
            final double now = Timer.getFPGATimestamp();

            DriveMotionPlanner.Output output =motionPlanner_.update(now, RobotState.getInstance().getFieldToVehicle(now));

            // DriveSignal signal = new DriveSignal(demand.left_feedforward_voltage / 12.0, demand.right_feedforward_voltage / 12.0);

           periodicIO_.error =motionPlanner_.error();
           periodicIO_.path_setpoint =motionPlanner_.setpoint();

            if (!overrideTrajectory_) {
                setVelocity(new DriveSignal(radiansPerSecondToTicksPer100ms(output.left_velocity), radiansPerSecondToTicksPer100ms(output.right_velocity)),
                        new DriveSignal(output.left_feedforward_voltage / 12.0, output.right_feedforward_voltage / 12.0));

               periodicIO_.left_accel = radiansPerSecondToTicksPer100ms(output.left_accel) / 1000.0;
               periodicIO_.right_accel = radiansPerSecondToTicksPer100ms(output.right_accel) / 1000.0;
            } else {
                setVelocity(DriveSignal.BRAKE, DriveSignal.BRAKE);
               periodicIO_.left_accel =periodicIO_.right_accel = 0.0;
            }
        } else {
            DriverStation.reportError("Drive is not in path following state", false);
        }
    }

    public synchronized void reloadGains() {
        leftMaster_.config_kP(kControlSlot, Constants.kDriveLowGearVelocityKp, Constants.kLongCANTimeoutMs);
        leftMaster_.config_kI(kControlSlot, Constants.kDriveLowGearVelocityKi, Constants.kLongCANTimeoutMs);
        leftMaster_.config_kD(kControlSlot, Constants.kDriveLowGearVelocityKd, Constants.kLongCANTimeoutMs);
        leftMaster_.config_kF(kControlSlot, Constants.kDriveLowGearVelocityKf, Constants.kLongCANTimeoutMs);
        leftMaster_.config_IntegralZone(kControlSlot, Constants.kDriveLowGearVelocityIZone, Constants.kLongCANTimeoutMs);

        rightMaster_.config_kP(kControlSlot, Constants.kDriveLowGearVelocityKp, Constants.kLongCANTimeoutMs);
        rightMaster_.config_kI(kControlSlot, Constants.kDriveLowGearVelocityKi, Constants.kLongCANTimeoutMs);
        rightMaster_.config_kD(kControlSlot, Constants.kDriveLowGearVelocityKd, Constants.kLongCANTimeoutMs);
        rightMaster_.config_kF(kControlSlot, Constants.kDriveLowGearVelocityKf, Constants.kLongCANTimeoutMs);
        rightMaster_.config_IntegralZone(kControlSlot, Constants.kDriveLowGearVelocityIZone, Constants.kLongCANTimeoutMs);
    }

    @Override
    public void writeToLog() {
        
    }

    @Override
    public synchronized void readPeriodicInputs() {
        double prevLeftTicks =periodicIO_.left_position_ticks;
        double prevRightTicks =periodicIO_.right_position_ticks;
       periodicIO_.left_position_ticks = leftMaster_.getSelectedSensorPosition(0);
       periodicIO_.right_position_ticks = rightMaster_.getSelectedSensorPosition(0);
       periodicIO_.left_velocity_ticks_per_100ms = leftMaster_.getSelectedSensorVelocity(0);
       periodicIO_.right_velocity_ticks_per_100ms = rightMaster_.getSelectedSensorVelocity(0);
        // The NavX rotates oposite of Pigion IMU
       periodicIO_.gyro_heading = Rotation2d.fromDegrees(imu_.getFusedHeading()).inverse().rotateBy(gyroOffset_.inverse());

        double deltaLeftTicks = ((periodicIO_.left_position_ticks - prevLeftTicks) / kDriveEncoderPPR) * Math.PI;
        if (deltaLeftTicks > 0.0) {
           periodicIO_.left_distance += deltaLeftTicks * Constants.kDriveWheelDiameterInches;
        } else {
           periodicIO_.left_distance += deltaLeftTicks * Constants.kDriveWheelDiameterInches;
        }

        double deltaRightTicks = ((periodicIO_.right_position_ticks - prevRightTicks) / kDriveEncoderPPR) * Math.PI;
        if (deltaRightTicks > 0.0) {
           periodicIO_.right_distance += deltaRightTicks * Constants.kDriveWheelDiameterInches;
        } else {
           periodicIO_.right_distance += deltaRightTicks * Constants.kDriveWheelDiameterInches;
        }

        if (csvWriter_ != null) {
           csvWriter_.add(periodicIO_);
        }

        // System.out.println(_periodicIO.gyro_heading.getDegrees());
        // System.out.println("control state: " +driveControlState_ + ", left: " +periodicIO_.left_demand + ", right: " +periodicIO_.right_demand);
    }

    @Override
    public synchronized void writePeriodicOutputs() {
        switch (driveControlState_) {
        case OPEN_LOOP:
            leftMaster_.set(ControlMode.PercentOutput,periodicIO_.left_demand, DemandType.ArbitraryFeedForward, 0.0);
            rightMaster_.set(ControlMode.PercentOutput,periodicIO_.right_demand, DemandType.ArbitraryFeedForward, 0.0);
            break;
        case PATH_FOLLOWING:
            leftMaster_.set(ControlMode.Velocity,periodicIO_.left_demand, DemandType.ArbitraryFeedForward,
                periodicIO_.left_feedforward + Constants.kDriveLowGearVelocityKd *periodicIO_.left_accel / 1023.0);
            rightMaster_.set(ControlMode.Velocity,periodicIO_.right_demand, DemandType.ArbitraryFeedForward,
                periodicIO_.right_feedforward + Constants.kDriveLowGearVelocityKd *periodicIO_.right_accel / 1023.0);
                break;
        case MANUAL:
            break;
        }
    }

    public synchronized void startLogging() {
        if (csvWriter_ == null) {
           csvWriter_ = new ReflectingCSVWriter<>("/home/lvuser/DRIVE-LOGS.csv", PeriodicIO.class);
        }
    }

    public synchronized void stopLogging() {
        if (csvWriter_ != null) {
           csvWriter_.flush();
           csvWriter_ = null;
        }
    }

    private static double rotationsToInches(double rotations) {
        return rotations * (Constants.kDriveWheelDiameterInches * Math.PI);
    }

    private static double rpmToInchesPerSecond(double rpm) {
        return rotationsToInches(rpm) / 60;
    }

    private static double inchesToRotations(double inches) {
        return inches / (Constants.kDriveWheelDiameterInches * Math.PI);
    }

    private static double inchesPerSecondToRpm(double inches_per_second) {
        return inchesToRotations(inches_per_second) * 60;
    }

    private static double radiansPerSecondToTicksPer100ms(double rad_s) {
        return rad_s / (Math.PI * 2.0) * Drive.kDriveEncoderPPR / 10.0;
    }

}