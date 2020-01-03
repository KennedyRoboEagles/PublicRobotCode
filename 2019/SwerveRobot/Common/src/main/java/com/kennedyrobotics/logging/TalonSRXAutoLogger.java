package com.kennedyrobotics.logging;

import badlog.lib.BadLog;
import com.ctre.phoenix.motorcontrol.can.TalonSRX;

/**
 * Auto Logger for Talon SRX
 * Based On: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/driver/CANTalonSRX.java
 */
public class TalonSRXAutoLogger implements AutoLogger<TalonSRX> {

    @Override
    public void log(String subsystemName, String combo, TalonSRX talon) {
        BadLog.createValue(combo + "Firmware", "" + talon.getFirmwareVersion());

        BadLog.createTopic(combo + "Output Percent", BadLog.UNITLESS, talon::getMotorOutputPercent,
                "join:" + subsystemName + "/Output Percents");

        BadLog.createTopic(combo + "Current", "A", talon::getOutputCurrent,
                "join:" + subsystemName + "/Output Currents");
        BadLog.createTopic(combo + "Temperature", "C", talon::getTemperature,
                "join:" + subsystemName + "/Temperatures");
    }
}
