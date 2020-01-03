package com.kennedyrobotics.logging;

/**
 * TODO
 * Based on https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/log/AutoLogger.java
 * @param <T>
 */
public interface AutoLogger<T> {
    void log(String subsystemName, String combo, T device);
}