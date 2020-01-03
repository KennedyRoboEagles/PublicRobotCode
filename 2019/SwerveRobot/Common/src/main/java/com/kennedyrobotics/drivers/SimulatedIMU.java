package com.kennedyrobotics.drivers;

import com.kennedyrobotics.drivers.HeadingProvider;
import com.team254.lib.geometry.Rotation2d;

public class SimulatedIMU implements HeadingProvider {

    private Rotation2d yaw_ = Rotation2d.identity();


    @Override
    public Rotation2d getHeading() {
        // TODO: Remove Rotation2D.fromDegress(0)
        return yaw_;
    }

    public void setHeading(Rotation2d angle) {
        yaw_ = new Rotation2d(angle);
    }

}
