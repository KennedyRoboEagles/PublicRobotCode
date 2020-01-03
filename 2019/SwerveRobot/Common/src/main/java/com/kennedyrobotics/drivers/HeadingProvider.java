package com.kennedyrobotics.drivers;

import com.team254.lib.geometry.Rotation2d;

public interface HeadingProvider {

    Rotation2d getHeading();

    void setHeading(Rotation2d heading);
}
