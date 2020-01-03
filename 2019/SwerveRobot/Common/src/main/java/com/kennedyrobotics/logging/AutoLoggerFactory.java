package com.kennedyrobotics.logging;

import com.ctre.phoenix.motorcontrol.can.TalonSRX;
import com.kauailabs.navx.frc.AHRS;
import com.revrobotics.CANSparkMax;

import java.util.HashMap;
import java.util.Map;

/**
 * TODO
 * TODO This may need to be modified to work with our library interfaces
 * Based on https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/log/AutoLoggerFactory.java
 */
public class AutoLoggerFactory {
    private static Map<Class<?>, AutoLogger<?>> loggers = new HashMap<>();

    static {
        register(CANSparkMax.class, new SparkMaxAutoLogger());
        register(TalonSRX.class, new TalonSRXAutoLogger());
        register(AHRS.class, new AHRSAutoLogger());
    }

    public static <T> void log(String subsystemName, String deviceName, T device) {
        AutoLogger<T> logger = (AutoLogger<T>) loggers.get(device.getClass());

        if (logger == null)
            throw new NoClassDefFoundError(
                    "No AutoLogger<" + device.getClass().getSimpleName() + "> was registered");
        else
            logger.log(subsystemName, subsystemName + "/" + deviceName + " ", device);
    }

    private static void register(Class<?> deviceType, AutoLogger<?> logger) {
        loggers.put(deviceType, logger);
    }
}