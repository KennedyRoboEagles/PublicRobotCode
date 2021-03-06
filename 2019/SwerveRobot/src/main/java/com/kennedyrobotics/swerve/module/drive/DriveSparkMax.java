package com.kennedyrobotics.swerve.module.drive;

import com.kennedyrobotics.drivers.SparkMaxUtil;
import com.kennedyrobotics.exceptions.TodoException;
import com.kennedyrobotics.swerve.module.MotorControlMode;
import com.revrobotics.CANEncoder;
import com.revrobotics.CANError;
import com.revrobotics.CANSparkMax;
import com.revrobotics.CANSparkMax.IdleMode;
import com.revrobotics.EncoderType;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

public class DriveSparkMax implements DriveMotor {

    private static int id = 0;

    private int id_;

    private final CANSparkMax controller_;
    private final CANEncoder encoder_;

    public DriveSparkMax(CANSparkMax controller) {
        id_ = id++;

        controller_ = controller;

        if (controller_ == null) {
            encoder_ = null;
            return;
        };

        // There is a bug with the spark max library that always sets the sensor kNoSensor
        CANError err = SparkMaxUtil.setSensorType(controller_, EncoderType.kHallSensor);
        if (err != CANError.kOk) {
            DriverStation.reportError("Unable to set kHallSensor for spark ID: " + controller_.getDeviceId(), false);
        }

        controller_.setOpenLoopRampRate(0.5);

        encoder_ = controller_.getEncoder();
        encoder_.setPositionConversionFactor(1); // TODO Figure out conversion factor encoder ticks -> inch
    }

    @Override
    public void initialize() {
        // There is a bug with the spark max library that always sets the sensor kNoSensor
        CANError err = SparkMaxUtil.setSensorType(controller_, EncoderType.kHallSensor);
        if (err != CANError.kOk) {
            DriverStation.reportError("Unable to set kHallSensor for spark ID: " + controller_.getDeviceId(), false);
        }
    }

    @Override
    public void set(MotorControlMode mode, double value) {
        if (controller_ == null) return;

        switch (mode) {
            case kPercentOutput:
            controller_.set(value);
            break;
        case kVelocity:
        case kPosition:
            throw new TodoException();
        default:
            throw new IllegalStateException("Unknown control mode: " + mode.toString());
        }

        SmartDashboard.putNumber("" + id_ + ": Spark Max applied output", controller_.getAppliedOutput());
        SmartDashboard.putNumber("" + id_ + ": Spark Max faults", controller_.getFaults());
        SmartDashboard.putNumber("" + id_
                + ": Spark Max Motor Temp", controller_.getMotorTemperature());
    }

    @Override
    public void setInverted(boolean inverted) {
        if (controller_ == null) return;

        controller_.setInverted(inverted);
    }

    @Override
    public void setBrake(boolean brake) {
        if (controller_ == null) return;

        controller_.setIdleMode(brake ? IdleMode.kBrake: IdleMode.kCoast);
    }

    @Override
    public void stopMotor() {
        if (controller_ == null) return;

        controller_.stopMotor();
    }

    @Override
    public void zeroEncoder() {
        encoder_.setPosition(0);
    }

    /**
     * Current position of encoder in inches
     * @return inches
     */
    @Override
    public double getPosition() {
        return encoder_.getPosition();
    }
}
