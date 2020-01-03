package com.kennedyrobotics.drivers.leds;

import com.ctre.phoenix.CANifier;
import com.kennedyrobotics.leds.CANifierLEDChannel;
import com.kennedyrobotics.leds.LEDChannel;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.mockito.Mockito;


public class CANifierLEDChannelTest {

    @Test
    public void sanityTest() {
        CANifier canifier = Mockito.mock(CANifier.class);

        canifier.setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelA);

        Mockito.verify(canifier).setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelA);
    }

    @Test
    public void channelIdTest() {
        Assertions.assertEquals(CANifier.LEDChannel.LEDChannelA, CANifierLEDChannel.getChannel(0));
        Assertions.assertEquals(CANifier.LEDChannel.LEDChannelB, CANifierLEDChannel.getChannel(1));
        Assertions.assertEquals(CANifier.LEDChannel.LEDChannelC, CANifierLEDChannel.getChannel(2));

        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            CANifierLEDChannel.getChannel(-1);
        });

        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            CANifierLEDChannel.getChannel(4);
        });
    }

    @Test
    public void test() {
        CANifier canifier = Mockito.mock(CANifier.class);

        LEDChannel ledChannel = new CANifierLEDChannel(canifier, 0);
        ledChannel.set(0.5);
        Mockito.verify(canifier, Mockito.times(1)).setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelA);

        canifier = Mockito.mock(CANifier.class);
        ledChannel = new CANifierLEDChannel(canifier, 1);
        ledChannel.set(0.5);
        Mockito.verify(canifier, Mockito.times(1)).setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelB);

        canifier = Mockito.mock(CANifier.class);
        ledChannel = new CANifierLEDChannel(canifier, 2);
        ledChannel.set(0.5);
        Mockito.verify(canifier, Mockito.times(1)).setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelC);
    }
}
