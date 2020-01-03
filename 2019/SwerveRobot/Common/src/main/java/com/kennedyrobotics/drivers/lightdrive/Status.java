package com.kennedyrobotics.drivers.lightdrive;
/**
 * LightDrive status
 * Bits:
 * 0 - Enabled
 * 1,2,3 - Mode
 * 4,5,6,7 - Triped flags
 */
public class Status {
    private final byte status_;

    /**
     * Light Drive status from status byte
     * @param status status byte from light drive
     */
    public Status(byte status) {
        status_ = status;
    }

    /**
     * Is the light drive enabled
     * @return is enabled
     */
    public boolean enabled() {
        return (status_ & 0b00000001) > 0;
    }

    /**
     * Current operating mode
     * @return mode
     */
    public Mode mode() {
        int m = (status_ & 0b00001110) >> 1;
        return Mode.from(m);
    }

    /**
     * Current trip on the led bank
     * @param bank id between 1 to 4
     * @return has the bank tripped
     */
    public boolean bankTrip(int bank) {
        switch (bank) {
            case 1:
                return (status_ & 0b00010000) > 0;
            case 2:
                return (status_ & 0b00100000) > 0;
            case 3:
                return (status_ & 0b01000000) > 0;
            case 4:
                return (status_ & 0b10000000) > 0;
        }

        throw new IllegalArgumentException("Invalid bank id");
    }

    @Override
    public boolean equals(Object other) {
        if (other instanceof Status) {
            return this.status_ == ((Status)other).status_;
        }
        return false;
    }
}
