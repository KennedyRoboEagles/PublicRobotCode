package com.kennedyrobotics.drivers;

import edu.wpi.first.wpilibj.I2C;

/**
 * Represents an Adafruit TCA9548A I2C Multiplexer which is used to toggle the I2C connection for
 * each of its 8 channels
 *
 * From: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/driver/AdafruitMultiplexer.java
 *
 * @see "https://www.adafruit.com/product/2717"
 * @see "https://cdn-shop.adafruit.com/datasheets/tca9548a.pdf"
 */
public class AdafruitMultiplexer extends I2C {
    public AdafruitMultiplexer(Port port, int deviceAddress) {
        super(port, deviceAddress);
    }

    /**
     * Disable all of the channels
     */
    public void reset() {
        byte[] buffer = new byte[1];
        buffer[0] = 0;
        writeBulk(buffer);
    }

    /**
     * Enable a given channel. This disables all other channels.
     *
     * @param channel the channel id that should be enabled
     */
    public void enableChannel(int channel) {
        byte[] buffer = new byte[1];
        buffer[0] = (byte) (1 << channel);
        writeBulk(buffer);
    }

    /**
     * Get the channel that is currently enabled.
     *
     * @return the currently enabled channel or 0 if no channels are enabled
     */
    public int getCurrentChannel() {
        byte[] buffer = new byte[1];
        readOnly(buffer, 1);
        return buffer[0];
    }
}