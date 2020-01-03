package com.kennedyrobotics.leds;

import com.ctre.phoenix.CANifier;

/**
 * LED channel on the CTRE CANifier.
 */
public class CANifierLEDChannel implements LEDChannel {

    private final CANifier canifier_;
    private final CANifier.LEDChannel ledChannel;

    public CANifierLEDChannel(CANifier canifier, int channelId) {
        canifier_ = canifier;
        ledChannel = getChannel(channelId);
    }


    @Override
    public void set(double brightness) {
        canifier_.setLEDOutput(brightness, ledChannel);
    }

    /**
     * Convert integer ID to CANifier Led channel
     * Mapping:
     * 0 - Channel A
     * 1 - Channel B
     * 2 - Channel C
     * @param id
     * @return
     */
    public static CANifier.LEDChannel getChannel(int id) {
        switch (id) {
        case 0:
            return CANifier.LEDChannel.LEDChannelA;
        case 1:
            return CANifier.LEDChannel.LEDChannelB;
        case 2:
            return CANifier.LEDChannel.LEDChannelC;
        }

        throw new IllegalArgumentException("Channel ID needs to be in range of 0 to 2");
    }
}
