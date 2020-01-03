package com.kennedyrobotics.logging;

import badlog.lib.BadLog;
import com.revrobotics.CANSparkMax;

/**
 * Spark Max Auto Logger
 * Based on: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/log/CANSparkMaxAutoLogger.java
 */
public class SparkMaxAutoLogger implements AutoLogger<CANSparkMax> {
    @Override
    public void log(String subsystemName, String combo, CANSparkMax spark) {
        BadLog.createValue(combo + "Firmware", spark.getFirmwareString());

        BadLog.createTopic(combo + "Output Percent", BadLog.UNITLESS, spark::get,
                "join:" + subsystemName + "/Output Percents");

        BadLog.createTopic(combo + "Current", "A", spark::getOutputCurrent,
                "join:" + subsystemName + "/Output Currents");
        BadLog.createTopic(combo + "Temperature", "C", spark::getMotorTemperature,
                "join:" + subsystemName + "/Temperatures");
    }
}
