package com.kennedyrobotics.logging;

/**
 * Represents a device that can be logged using {@link badlog.lib.BadLog}
 * Based on https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/log/Loggable.java
 */
public interface Loggable {
    void initLogging();
}
