package com.kennedyrobotics.swerve.module.hardware;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.*;
import com.kennedyrobotics.CANConstants;
import com.kennedyrobotics.exceptions.TodoException;
import com.kennedyrobotics.swerve.module.drive.DriveMotor;
import com.kennedyrobotics.swerve.signals.ModuleSignal;
import com.kennedyrobotics.swerve.module.ModuleBase;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.kennedyrobotics.swerve.module.ModuleUtil;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class KennedyModule extends ModuleBase {
    private static final double kSteerNativeUnitsPerRotationQuad = 4 * 7 * 71 * 40.0/48.0;
    public static final double kSteerNativeUnitsPerRotationAbs = 1023;
    public static final int kSteerPIDId = 0;

    public static final int kSteerAngleToleranceDegrees = 4; //TODO Figure out

    /**
     * Operating mode of the steering motor.
     */
    public enum EncoderType {
        kQuadrature,
        kAbsolute,
    }

    public static class Config {
        public double kP;
        public double kI;
        public double kD;

        @Deprecated
        public double nativeUnitsPerRotationAbs;
        public Rotation2d moduleOffset = Rotation2d.identity();

        // Odometry config
        public Translation2d startingPosition;
        public ModuleOdometry.Config odomConfig;
    }

//    public static Config getDefaultConfig() {
//        return getDefaultConfig(0, 0, 0, new ModuleOdometry.Config(1, 1, 1, false));
//    }

    public static Config getDefaultConfig(double p, double i, double d, ModuleOdometry.Config odomConfig) {
        Config config = new Config();
        config.kP = p;
        config.kI = i;
        config.kD = d;

        config.odomConfig = odomConfig;

        config.nativeUnitsPerRotationAbs = kSteerNativeUnitsPerRotationAbs;
        config.moduleOffset = Rotation2d.identity();

        return config;
    }

    private class PeriodicIO {
        boolean ready = false;

        // INPUTS
        int absoluteAngleRaw;
        int absoluteAngleRadians;
        Rotation2d absoluteAngle;
        double steerClosedLoopError;


        // OUTPUTS
        boolean brakeMode;
        MotorControlMode controlMode;
        double driveDemand;
        Rotation2d goalAngle = Rotation2d.identity();
        boolean allowReverse;
    }


    private final double kSteerVoltageRamp = 0.1;

    private final Config config_;
    private final ModuleID moduleID_;
    private final DriveMotor drive_;
    private final IMotorControllerEnhanced steer_;

    private boolean inverted_;

    private PeriodicIO periodicIO_ = new PeriodicIO();

    public KennedyModule(ModuleID moduleID, Config config, IMotorControllerEnhanced steer, DriveMotor drive) {
        super(moduleID, config.odomConfig, config.startingPosition);
        moduleID_ = moduleID;
        config_ = config;

        /*
         * Configure Drive motor
         */
        drive_ = drive;
        drive_.setInverted(false);

        /*
         * Configure Steer motor 
         */
        steer_ = steer;
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_1_General, 10, 100);
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_2_Feedback0, 20, 100);
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_3_Quadrature, 1000, 100);
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_4_AinTempVbat, 1000, 100);
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_8_PulseWidth, 1000, 100);
        steer_.setStatusFramePeriod(StatusFrameEnhanced.Status_12_Feedback1, 1000, 100);

        final ErrorCode sensorPresent = steer_.configSelectedFeedbackSensor(FeedbackDevice
            .Analog, 0, 100); //primary closed-loop, 100 ms timeout
        if (sensorPresent != ErrorCode.OK) {
            DriverStation.reportError("Could not detect " + moduleID_.name + " encoder: " + sensorPresent, false);
        }

        steer_.setInverted(true);
        steer_.setSensorPhase(false);
        steer_.enableVoltageCompensation(true);
        steer_.configVoltageCompSaturation(12.0, CANConstants.kLongTimeoutMs); // TODO Should this be change to something like 10v
        steer_.configVelocityMeasurementPeriod(VelocityMeasPeriod.Period_50Ms, CANConstants.kLongTimeoutMs);
        steer_.configVelocityMeasurementWindow(1, CANConstants.kLongTimeoutMs);
        steer_.configClosedloopRamp(kSteerVoltageRamp, CANConstants.kLongTimeoutMs);
        steer_.configNeutralDeadband(0.04, 0);
        steer_.setNeutralMode(NeutralMode.Brake);

        steer_.config_kP(kSteerPIDId, config.kP, CANConstants.kLongTimeoutMs);
        steer_.config_kI(kSteerPIDId, config.kI, CANConstants.kLongTimeoutMs);
        steer_.config_kD(kSteerPIDId, config.kD, CANConstants.kLongTimeoutMs);
    }

    public IMotorControllerEnhanced getSteer() { return steer_; }
    public DriveMotor getDrive() { return drive_; }

    /**
     * (re)Initialize the module for use
     */
    public synchronized void initialize() {
        System.out.println("Initializing module " + moduleID_.name);
        if (!periodicIO_.ready) {
            // Force a IO read
            this.readPeriodicInputs();
        }

        drive_.initialize();
    }

    public synchronized void sendSignal(ModuleSignal state) {
        periodicIO_.controlMode = state.controlMode;
        periodicIO_.driveDemand = state.demand;
        periodicIO_.goalAngle = state.angle;
        periodicIO_.allowReverse = state.allowReverse;
        periodicIO_.brakeMode = state.brake;
    }

    /**
     * Convert the given angle in degrees to talon native units
     * @param angle degrees 
     * @return angle in native units
     */
    private double angleToNative(double angle, EncoderType type) {
        switch (type) {
        // case kQuadrature:
        //     return config_.nativeUnitsPerRotationQuad * (angle / (2.0*Math.PI));
        case kAbsolute:
            return config_.nativeUnitsPerRotationAbs * (angle / (2.0*Math.PI));
        default:
            throw new IllegalStateException();
        }
    }

    /**
     * Convert the given angle in talon native units to radians
     * @param nativeValue angle in native units
     * @return angle in radians 
     */
    private double nativeToAngle(double nativeValue, EncoderType type) {
        switch (type) {
        // case kQuadrature:
        //    return nativeValue * (2.0 * Math.PI) / config_.nativeUnitsPerRotationQuad;
        case kAbsolute:
            return nativeValue * (2.0 * Math.PI) / config_.nativeUnitsPerRotationAbs;
        default:
            throw new IllegalStateException();
        }
    }

    /**
     * Read in sensor data
     */
    @Override
    public synchronized void readPeriodicInputs() {
        periodicIO_.steerClosedLoopError = steer_.getClosedLoopError(kSteerPIDId)/config_.nativeUnitsPerRotationAbs;

        periodicIO_.absoluteAngleRaw = steer_.getSelectedSensorPosition(0);
        periodicIO_.absoluteAngle = Rotation2d.fromRadians(nativeToAngle(
                periodicIO_.absoluteAngleRaw, EncoderType.kAbsolute
        )).rotateBy(config_.moduleOffset.inverse());

        periodicIO_.ready = true;
    }

    /**
     * Handle setting drive, and drive commands
     */
    @Override
    public synchronized void writePeriodicOutputs() {
        double driveDemand = periodicIO_.driveDemand;

        double currentAngle = periodicIO_.absoluteAngle.getRadians();
        double goalAngle = periodicIO_.goalAngle.getRadians();
        double angleError = Math.IEEEremainder(goalAngle - currentAngle, 2.0*Math.PI);

        SmartDashboard.putNumber(moduleID_.name + " Angle Error", Math.toDegrees(angleError));
        // Minimize azimuth rotation, reversing drive if necessary
        inverted_ = Math.abs(angleError) > (Math.PI/4.0);
        // System.out.println("Inverted: " + inverted_);

        if (periodicIO_.allowReverse && inverted_) {
            angleError -= Math.copySign(Math.PI, angleError);
            driveDemand *= -1;
        }
        steer_.set(ControlMode.Position, periodicIO_.absoluteAngleRaw + angleToNative(angleError, EncoderType.kAbsolute));

        drive_.setBrake(periodicIO_.brakeMode);
        drive_.set(periodicIO_.controlMode, driveDemand);
    }

    @Override
    public boolean checkSystem() {
        return false;
    }

    /**
     * Push telemetry will publish debug related data to the smartdashboard, or badlog
     */
    @Override
    public synchronized void outputTelemetry() {
        SmartDashboard.putNumber(moduleID_.name + " Steer Closed Loop Error", periodicIO_.steerClosedLoopError);
        SmartDashboard.putString(moduleID_.name + " Drive Control Mode", periodicIO_.controlMode.name());
        SmartDashboard.putNumber(moduleID_.name + " Drive Demand", periodicIO_.driveDemand);
        SmartDashboard.putNumber(moduleID_.name + " Abs Raw", periodicIO_.absoluteAngleRaw);
        SmartDashboard.putNumber(moduleID_.name + " Abs Angle", periodicIO_.absoluteAngle.getDegrees());
    }

    @Override
    public void neutralOutput() {
        drive_.stopMotor();
        steer_.neutralOutput();

        periodicIO_.controlMode = MotorControlMode.kNeutralOutput;
        periodicIO_.driveDemand = 0;
    }

    /**
     * Current angle of swerve module. This is not reflect if the module is currently inverted
     * @return angle
     */
    public Rotation2d moduleAngle() {
        return periodicIO_.absoluteAngle;
    } 

    public boolean angleOnTarget() {
        // TODO(Ryan): Need to take make sure that we are taking account when the module is reversed
        return ModuleUtil.angleOnTarget(periodicIO_.goalAngle, moduleAngle(), kSteerAngleToleranceDegrees);
    }

    public MotorControlMode controlMode() {
        return periodicIO_.controlMode;
    }

    public double driveDistance() {
        return drive_.getPosition();
    }

    public boolean drivePositionOnTarget() {
        throw new TodoException();
    }

    public void setNominalDriveOutput(double voltage) {
        throw new TodoException();
    }

    public void set10VoltRotationMode(boolean enable) {
        throw new TodoException();
    }

    public void setMaxRotationSpeed(double maxRotationSpeed) {
        // TODO(Ryan) This is a nice to have
    }
} 
