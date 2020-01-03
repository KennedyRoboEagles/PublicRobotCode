package com.kennedyrobotics.drivers.lightdrive;

/**
 * Current operating mode of the light drive.
 */
public enum Mode {
    kNoSignal(0),
    kPWM(1),
    kCAN(2),
    kSerial(3);

    private final int id_;
    Mode(int id) {
        id_ = id;
    }

    public static Mode from(int id) {
        switch(id) {
            case 0:
                return kNoSignal;
            case 1:
                return kPWM;
            case 2:
                return kCAN;
            case 3:
                return kSerial;
        }

        throw new IllegalArgumentException("Invalid ID: " + id);
    }
}
