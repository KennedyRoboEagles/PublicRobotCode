package com.kennedyrobotics.drivers.leds;

import com.ctre.phoenix.CANifier;
import com.kennedyrobotics.leds.CANifierColorChannel;
import com.kennedyrobotics.leds.Color;
import com.kennedyrobotics.leds.ColorChannel;
import org.junit.jupiter.api.Test;
import org.mockito.ArgumentMatchers;
import org.mockito.Mockito;


public class CANifierColorChannelTest {

    @Test
    public void sanityTest() {
        CANifier canifier = Mockito.mock(CANifier.class);

        canifier.setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelA);

        Mockito.verify(canifier).setLEDOutput(0.5, CANifier.LEDChannel.LEDChannelA);
    }

    @Test
    public void testSet() {
        CANifier canifier = Mockito.mock(CANifier.class);

        Color color = new Color(10, 20, 30);

        ColorChannel colorChannel = new CANifierColorChannel(canifier);
        colorChannel.set(color);

        Mockito.verify(canifier, Mockito.times(3)).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.any());
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelA));
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelB));
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelC));

        Mockito.verify(canifier).setLEDOutput(10.0/255.0, CANifier.LEDChannel.LEDChannelA);
        Mockito.verify(canifier).setLEDOutput(20.0/255.0, CANifier.LEDChannel.LEDChannelB);
        Mockito.verify(canifier).setLEDOutput(30.0/255.0, CANifier.LEDChannel.LEDChannelC);
    }

    @Test
    public void testSetBrightness() {
        CANifier canifier = Mockito.mock(CANifier.class);

        Color color = new Color(10, 20, 30);

        ColorChannel colorChannel = new CANifierColorChannel(canifier);
        colorChannel.set(color, 0.5);

        Mockito.verify(canifier, Mockito.times(3)).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.any());
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelA));
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelB));
        Mockito.verify(canifier).setLEDOutput(ArgumentMatchers.anyDouble(), ArgumentMatchers.eq(CANifier.LEDChannel.LEDChannelC));

        Mockito.verify(canifier).setLEDOutput(10.0/255.0 * 0.5, CANifier.LEDChannel.LEDChannelA);
        Mockito.verify(canifier).setLEDOutput(20.0/255.0 * 0.5, CANifier.LEDChannel.LEDChannelB);
        Mockito.verify(canifier).setLEDOutput(30.0/255.0 * 0.5, CANifier.LEDChannel.LEDChannelC);
    }


}
