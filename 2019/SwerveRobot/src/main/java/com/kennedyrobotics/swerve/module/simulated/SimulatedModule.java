package com.kennedyrobotics.swerve.module.simulated;

import com.kennedyrobotics.exceptions.TodoException;
import com.kennedyrobotics.swerve.signals.ModuleSignal;
import com.kennedyrobotics.swerve.module.ModuleBase;
import com.kennedyrobotics.swerve.odom.ModuleOdometry;
import com.kennedyrobotics.swerve.module.ModuleID;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import com.team254.lib.geometry.Rotation2d;
import com.team254.lib.geometry.Translation2d;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.Constants;


public class SimulatedModule extends ModuleBase {

    private class PeriodicIO {
        // Outputs
        MotorControlMode driveMode = MotorControlMode.kNeutralOutput;
        double driveDemand;

        MotorControlMode rotationMode = MotorControlMode.kNeutralOutput;
        double rotationDemand;
    }

    private final PeriodicIO io_ = new PeriodicIO();
    private final SimulatedMotor drive_;// = new SimulatedMotor(Constants.kSwerveDriveMaxSpeed * 0.5);
    private final SimulatedMotor rotation_; //= new SimulatedMotor(Constants.kSwerveRotationMaxSpeed * 0.5); // TODO not sure of units

    private boolean inverted_ = false;

    private final String name_;

    public SimulatedModule(ModuleID moduleID, ModuleOdometry.Config config, Translation2d startingPosition) {
        super(moduleID, config, startingPosition);
        name_ = moduleID.name;
        drive_ = new SimulatedMotor(name_ + "Drive", Constants.kSwerveDriveMaxSpeed * 0.5);
        rotation_ = new SimulatedMotor(name_ + "Rotation", Constants.kSwerveRotationMaxSpeed * 0.5); // TODO not sure of units
    }

    @Override
    public void setNominalDriveOutput(double voltage) {}

    @Override
    public void set10VoltRotationMode(boolean enable) {}

    protected void setBrake(boolean enabled) {
        drive_.setBrake(enabled);
    }

    @Override
    public double driveDistance() {
        // @TODO(Ryan): WTF Why does this need to be inverted
        return drive_.encoderPosition();
    }

    @Override
    public Rotation2d moduleAngle() {
        return Rotation2d.fromDegrees(rotation_.encoderPosition());
    }

    @Override
    public MotorControlMode controlMode() {
        return drive_.controlMode();
    }

    protected void setDrive(MotorControlMode mode, double demand) {
//        drive_.setDrive(mode, demand);
        if (inverted_) {
            demand *= -1;
        }

        io_.driveMode = mode;
        io_.driveDemand = demand;
    }

    protected void setRotation(Rotation2d goalAngle, boolean allowReverse) {

        // TODO(Ryan): This might be wrong
        inverted_ = false;
        double angleError = Math.IEEEremainder(goalAngle.getRadians() - moduleAngle().getRadians(), 2.0*Math.PI);
        boolean shouldInvert = Math.abs(angleError) > (Math.PI/4.0);
        if (allowReverse && shouldInvert) {
            goalAngle = goalAngle.rotateBy(Rotation2d.fromDegrees(180));
            inverted_ = true;
        }


//        rotation_.setDrive(MotorControlMode.kPosition, goalAngle.getDegrees());
        io_.rotationMode = MotorControlMode.kPosition;
        io_.rotationDemand = goalAngle.getDegrees();
    }

    @Override
    public void sendSignal(ModuleSignal signal) {
        this.setRotation(signal.angle, signal.allowReverse);
        this.setDrive(signal.controlMode, signal.demand);
        this.setBrake(signal.brake);
    }


    @Override
    public void neutralOutput() {
        drive_.neutralOutput();
        rotation_.neutralOutput();
    }

    @Override
    public void writePeriodicOutputs() {
        if (name_!=null) {
            SmartDashboard.putNumber(name_+ " Last write", Timer.getFPGATimestamp());
            System.out.println(name_ + ": " + io_.driveMode + ", " + io_.driveDemand + "  " + io_.rotationMode + ", " + io_.rotationDemand);
        }
        drive_.setDrive(io_.driveMode, io_.driveDemand);
        rotation_.setDrive(io_.rotationMode, io_.rotationDemand);
    }

    @Override
    public boolean checkSystem() {
        return false;
    }

    @Override
    public void readPeriodicInputs() {

    }

    @Override
    public boolean angleOnTarget() {
        // @TODO(Ryan): Should move to module base
        double error = Math.abs(io_.rotationDemand - this.moduleAngle().getDegrees());
        return error < 4.5;
    }

    @Override
    public boolean drivePositionOnTarget() {
        throw new TodoException();
    }

    @Override
    public synchronized void outputTelemetry() {
        super.outputTelemetry();
    }

    @Override
    public void stop() {
        this.setDrive(MotorControlMode.kNeutralOutput, 0);
    }

    @Override
    public void setMaxRotationSpeed(double maxRotationSpeed) {
        throw new TodoException();
    }
}
