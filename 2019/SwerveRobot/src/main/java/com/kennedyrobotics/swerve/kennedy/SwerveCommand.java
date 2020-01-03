package com.kennedyrobotics.swerve.kennedy;

import com.kennedyrobotics.swerve.signals.ModuleSignal;

public class SwerveCommand {
    public SwerveCommand() {
        frontRight = new ModuleSignal();
        frontLeft = new ModuleSignal();
        backLeft = new ModuleSignal();
        backRight = new ModuleSignal();
    }

    public ModuleSignal frontRight;
    public ModuleSignal frontLeft;
    public ModuleSignal backRight;
    public ModuleSignal backLeft;

    public void setBrake(boolean brake) {
        frontLeft.brake = brake;
        frontRight.brake = brake;
        backLeft.brake = brake;
        backRight.brake = brake;
    }
}
