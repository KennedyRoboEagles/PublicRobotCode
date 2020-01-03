package com.kennedyrobotics.swerve.module.drive;

import com.kennedyrobotics.swerve.module.MotorControlMode;

public interface DriveMotor {

    void set(MotorControlMode mode, double value);
    void initialize();
    void setInverted(boolean inverted);
    void setBrake(boolean brake);
    void stopMotor();
    void zeroEncoder();
    double getPosition();
}
