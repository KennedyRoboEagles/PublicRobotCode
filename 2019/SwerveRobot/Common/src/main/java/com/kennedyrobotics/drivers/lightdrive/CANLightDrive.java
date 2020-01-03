package com.kennedyrobotics.drivers.lightdrive;

import com.kennedyrobotics.leds.Color;
import edu.wpi.first.hal.can.CANJNI;
import edu.wpi.first.hal.can.CANMessageNotFoundException;
import edu.wpi.first.hal.util.UncleanStatusException;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * LightDrive 12 driver using the CAN bus
 */
public class CANLightDrive implements LightDrive {

    private static int kAddress = 0x02050000;
    private static int kStatusMessageMask = 0x1FFFFFFF;
    private static int kCANPeriodMs = 100;

    private final double[] ledCommands_;
    private final ByteBuffer statusMessageId_;
    private final ByteBuffer timestamp_;

    private FeedBackMessage feedBackMessage_;

    public CANLightDrive() {
        ledCommands_ = new double[12];
        statusMessageId_ = ByteBuffer.allocateDirect(4);
        statusMessageId_.order(ByteOrder.LITTLE_ENDIAN);

        timestamp_ = ByteBuffer.allocateDirect(4);
        timestamp_.order(ByteOrder.LITTLE_ENDIAN);
    }

    @Override
    public void setColor(int colorChannel, Color color) {
        this.setColor(colorChannel, color, 1.0);
    }

    @Override
    public void setColor(int colorChannel, Color color, double brightness) {
        this.setLed(3*colorChannel+1, color.red()/255.0 * brightness);
        this.setLed(3*colorChannel+2, color.green()/255.0 * brightness);
        this.setLed(3*colorChannel+3, color.blue()/255.0 * brightness);
    }

    @Override
    public void setLed(int channel, double brightness) {
        if (channel < 1 && 12 < channel) {
            throw new IllegalArgumentException("Light drive channel needs to be in the range of 1 to 12");
        }

        ledCommands_[channel] = brightness;
    }

    @Override
    public void update() {

        try {
            byte[] txData = new byte[6];
            // Send channels 1-6
            for (int i = 0; i < 6; i++) {
                txData[i] = (byte)(ledCommands_[i] * 255);
            }
            CANJNI.FRCNetCommCANSessionMuxSendMessage(kAddress, txData, kCANPeriodMs);

            // Send Channels 7-12
            for (int i = 0; i < 6; i++) {
                txData[i] = (byte)(ledCommands_[6+i] * 255);
            }
            CANJNI.FRCNetCommCANSessionMuxSendMessage(kAddress, txData, kCANPeriodMs);

        } catch(UncleanStatusException e) {
            // Ignore exception
        }

        // Receive status message
        try {
            statusMessageId_.putInt(kAddress+4);
            statusMessageId_.rewind();

            byte[] feedbackData = CANJNI.FRCNetCommCANSessionMuxReceiveMessage(
                    statusMessageId_.asIntBuffer(),
                    kStatusMessageMask,
                    timestamp_
            );

            feedBackMessage_ = new FeedBackMessage(feedbackData);
        } catch (CANMessageNotFoundException e) {
            // Ignore exception
        }
    }

    @Override
    public FeedBackMessage feedback() {
        return feedBackMessage_;
    }
}
