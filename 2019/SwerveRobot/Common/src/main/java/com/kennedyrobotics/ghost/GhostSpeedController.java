package com.kennedyrobotics.ghost;

import edu.wpi.first.wpilibj.SpeedController;

public class GhostSpeedController implements SpeedController {

    private boolean inverted_;
    private double speed_;

    @Override
    public void pidWrite(double output) {
        speed_ = output;
    }

    @Override
    public void set(double speed) {
        speed_ = speed;
    }

    @Override
    public double get() {
        return speed_;
    }

    @Override
    public void setInverted(boolean isInverted) {
        inverted_ = isInverted;
    }

    @Override
    public boolean getInverted() {
        return inverted_;
    }

    @Override
    public void disable() {

    }

    @Override
    public void stopMotor() {

    }

}