package com.kennedyrobotics.drivers.lightdrive;

/**
 * Feedback message from the light drive
 */
public class FeedBackMessage {
    private final byte[] message_;
    private final Status status_;

    public FeedBackMessage(byte[] message) {
        if (message == null) {
            throw new IllegalArgumentException("Message must not be null");
        }
        if (message.length != 8) {
            throw new IllegalArgumentException("Message must be 8 bytes long");
        }

        message_ = message;
        status_ = new Status(message[5]);
    }

    /**
     * Current draw of bank in amps
     * @param bank id between 1 to 4
     * @return Current draw (amps)
     */
    public double current(int bank) {
        if (bank < 1 || 4 < bank) {
            throw new IllegalArgumentException("Invalid bank id");
        }

        int i = bank - 1;
        return message_[i] / 10.0;
    }

    /**
     * Total current draw of light drive
     * @return current draw in amps
     */
    public double totalCurrent() {
        return current(1) + current(2) + current(3) + current(4);
    }

    /**
     * Supply voltage to LightDrive
     * @return volts
     */
    public double inputVoltage() {
        return message_[4] / 10.0;
    }

    /**
     * Get the current light drive status
     * @return current status
     */
    public Status status() {
        return status_;
    }

    /**
     * Get the firmware version
     * @return version
     */
    public int firmware() {
        return message_[7];
    }

}
