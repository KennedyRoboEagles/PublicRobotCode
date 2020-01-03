package com.kennedyrobotics.logging;

import badlog.lib.BadLog;
import com.kauailabs.navx.frc.AHRS;

/**
 * NavX (AHRS) Auto logger
 * Based on: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/log/AHRSAutoLogger.java
 */
public class AHRSAutoLogger implements AutoLogger<AHRS> {

    @Override
    public void log(String subsystemName, String combo, AHRS navx) {
        BadLog.createValue(combo + "Firmware", navx.getFirmwareVersion());

        BadLog.createTopic(combo + "Temperature", "C", () -> (double) navx.getTempC(),
                "join:" + subsystemName + "/Temperatures");

        BadLog.createTopic(combo + "Pitch", "deg", () -> (double) navx.getPitch());
        BadLog.createTopic(combo + "Yaw", "deg", () -> (double) navx.getYaw());
        BadLog.createTopic(combo + "Roll", "deg", () -> (double) navx.getRoll());

        BadLog.createTopic(combo + "Velocity X", "M", () -> (double) navx.getVelocityX());
        BadLog.createTopic(combo + "Velocity Y", "M", () -> (double) navx.getVelocityY());
    }
}
