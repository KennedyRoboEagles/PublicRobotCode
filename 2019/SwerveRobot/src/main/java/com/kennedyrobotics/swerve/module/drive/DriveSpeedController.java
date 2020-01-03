package com.kennedyrobotics.swerve.module.drive;

import com.kennedyrobotics.swerve.module.MotorControlMode;
import edu.wpi.first.wpilibj.SpeedController;

public class DriveSpeedController implements DriveMotor {

    private final SpeedController controller_;

    public DriveSpeedController(SpeedController controller) {
        controller_ = controller;
    }

    @Override
    public void initialize() {
    }

    @Override
    public void set(MotorControlMode mode, double value) {
        if (MotorControlMode.kPercentOutput != mode) {
            throw new IllegalStateException("SpeedController only supports PercentOutput");
        }

        controller_.set(value);
    }

    @Override
    public void setInverted(boolean inverted) {
        controller_.setInverted(inverted);
    }

    @Override
    public void setBrake(boolean brake) {
        // WPI Speedcontroller does not support this feature
    }

    @Override
    public void stopMotor() {
        controller_.stopMotor();
    }

    @Override
    public void zeroEncoder() {

    }

    @Override
    public double getPosition() {
        return 0;
    }
}
