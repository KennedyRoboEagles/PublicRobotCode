package com.kennedyrobotics.drivers;

import badlog.lib.BadLog;
import com.kennedyrobotics.logging.Loggable;
import edu.wpi.first.wpilibj.Joystick;

/**
 * TODO
 * Based on: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/driver/Extreme3DProJoystick.java
 */
public class Extreme3DProJoystick extends Joystick implements Loggable {
    public Extreme3DProJoystick(int port) {
        super(port);
        initLogging();
    }

    public boolean getPovUp() {
        return getPOV() == 0;
    }

    public boolean getPovDown() {
        return getPOV() == 180;
    }

    public boolean getPovLeft() {
        return getPOV() == 270;
    }

    public boolean getPovRight() {
        return getPOV() == 90;
    }

    public boolean getSideThumbButton() {
        return getRawButton(2);
    }

    public boolean getTopBackLeftButton() {
        return getRawButton(3);
    }

    public boolean getTopBackRightButton() {
        return getRawButton(4);
    }

    public boolean getTopFrontLeftButton() {
        return getRawButton(5);
    }

    public boolean getTopFrontRightButton() {
        return getRawButton(6);
    }

    public boolean getButton7() {
        return getRawButton(7);
    }

    public boolean getButton8() {
        return getRawButton(8);
    }

    public boolean getButton9() {
        return getRawButton(9);
    }

    public boolean getButton10() {
        return getRawButton(10);
    }

    public boolean getButton11() {
        return getRawButton(11);
    }

    public boolean getButton12() {
        return getRawButton(12);
    }

    @Override
    public void initLogging() {
        String name = getClass().getSimpleName();
        BadLog.createTopic(name + "X", BadLog.UNITLESS, this::getX);
        BadLog.createTopic(name + "Y", BadLog.UNITLESS, this::getY);
        BadLog.createTopic(name + "Z", BadLog.UNITLESS, this::getZ);
        BadLog.createTopic(name + "Throttle", BadLog.UNITLESS, this::getThrottle);
    }
}