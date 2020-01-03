package com.kennedyrobotics.drivers;

import com.kauailabs.navx.frc.AHRS;
import com.team254.lib.geometry.Rotation2d;

public class AHRSHeadingProvider implements HeadingProvider {

    private final AHRS ahrs_;

    private Rotation2d gyroOffset_;
    private Rotation2d heading_;

    public AHRSHeadingProvider(AHRS ahrs) {
        ahrs_ = ahrs;
        gyroOffset_ = Rotation2d.identity();
        heading_ = Rotation2d.identity();
    }

    @Override
    public Rotation2d getHeading() {
        return Rotation2d.fromDegrees(ahrs_.getFusedHeading()).inverse().rotateBy(gyroOffset_.inverse());
    }

    @Override
    public void setHeading(Rotation2d heading) {
        gyroOffset_ = heading.rotateBy(Rotation2d.fromDegrees(ahrs_.getFusedHeading()).inverse());
    }
}
