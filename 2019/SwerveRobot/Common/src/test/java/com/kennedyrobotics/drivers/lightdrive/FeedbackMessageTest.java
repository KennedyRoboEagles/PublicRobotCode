package com.kennedyrobotics.drivers.lightdrive;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class FeedbackMessageTest {
    public static final double kTestEpsilon = 1e-5;

    @Test
    public void constructorTest() {
        FeedBackMessage msg = new FeedBackMessage(new byte[8]);
        assertEquals(0, msg.current(1), kTestEpsilon);
        assertEquals(0, msg.current(2), kTestEpsilon);
        assertEquals(0, msg.current(3), kTestEpsilon);
        assertEquals(0, msg.current(4), kTestEpsilon);
        assertEquals(0, msg.totalCurrent(), kTestEpsilon);
        assertEquals(0, msg.inputVoltage(), kTestEpsilon);
        assertEquals(0, msg.firmware());

        assertFalse(msg.status().enabled());
        assertFalse(msg.status().bankTrip(1));
        assertFalse(msg.status().bankTrip(2));
        assertFalse(msg.status().bankTrip(3));
        assertFalse(msg.status().bankTrip(4));
        assertEquals(Mode.kNoSignal, msg.status().mode());

        assertThrows(IllegalArgumentException.class, () -> new FeedBackMessage(new byte[15]));
        assertThrows(IllegalArgumentException.class, () -> new FeedBackMessage(new byte[17]));
        assertThrows(IllegalArgumentException.class, () -> new FeedBackMessage(null));
    }

    @Test
    public void currentTest() {
        byte[] data = new byte[8];
        final FeedBackMessage m = new FeedBackMessage(data);

        assertEquals(0, m.current(1), kTestEpsilon);
        assertEquals(0, m.current(2), kTestEpsilon);
        assertEquals(0, m.current(3), kTestEpsilon);
        assertEquals(0, m.current(4), kTestEpsilon);
        assertEquals(0, m.totalCurrent(), kTestEpsilon);
        assertFalse(m.status().enabled());
        assertFalse(m.status().bankTrip(1));
        assertFalse(m.status().bankTrip(2));
        assertFalse(m.status().bankTrip(3));
        assertFalse(m.status().bankTrip(4));
        assertEquals(Mode.kNoSignal, m.status().mode());

        assertThrows(IllegalArgumentException.class, () -> m.current(0));
        assertThrows(IllegalArgumentException.class, () -> m.current(5));

        data = new byte[8];
        data[0] = 25;
        data[1] = 35;
        data[2] = 45;
        data[3] = 55;
        FeedBackMessage msg = new FeedBackMessage(data);

        assertEquals(2.5, msg.current(1), kTestEpsilon);
        assertEquals(3.5, msg.current(2), kTestEpsilon);
        assertEquals(4.5, msg.current(3), kTestEpsilon);
        assertEquals(5.5, msg.current(4), kTestEpsilon);
        assertEquals(16.0, msg.totalCurrent(), kTestEpsilon);
    }

    @Test
    public void inputVoltageTest() {
        byte[] data = new byte[8];
        FeedBackMessage m = new FeedBackMessage(data);
        assertEquals(0, m.current(1), kTestEpsilon);
        assertEquals(0, m.current(2), kTestEpsilon);
        assertEquals(0, m.current(3), kTestEpsilon);
        assertEquals(0, m.current(4), kTestEpsilon);
        assertEquals(0, m.totalCurrent(), kTestEpsilon);
        assertEquals(0, m.firmware());

        assertEquals(0,m.inputVoltage(), kTestEpsilon);

        data = new byte[8];
        data[4] = 14;
        m = new FeedBackMessage(data);
        assertEquals(0, m.current(1), kTestEpsilon);
        assertEquals(0, m.current(2), kTestEpsilon);
        assertEquals(0, m.current(3), kTestEpsilon);
        assertEquals(0, m.current(4), kTestEpsilon);
        assertEquals(0, m.totalCurrent(), kTestEpsilon);
        assertEquals(new Status((byte)0), m.status());

        assertEquals(1.4, m.inputVoltage(), kTestEpsilon);
    }

    @Test
    public void firmwareTest() {
        byte[] data = new byte[8];
        data[7] = 123;
        FeedBackMessage m = new FeedBackMessage(data);
        assertEquals(0, m.current(1), kTestEpsilon);
        assertEquals(0, m.current(2), kTestEpsilon);
        assertEquals(0, m.current(3), kTestEpsilon);
        assertEquals(0, m.current(4), kTestEpsilon);
        assertEquals(0, m.totalCurrent(), kTestEpsilon);
        assertEquals(0, m.inputVoltage(), kTestEpsilon);
        assertFalse(m.status().enabled());
        assertFalse(m.status().bankTrip(1));
        assertFalse(m.status().bankTrip(2));
        assertFalse(m.status().bankTrip(3));
        assertFalse(m.status().bankTrip(4));
        assertEquals(Mode.kNoSignal, m.status().mode());


        assertEquals(123, m.firmware());
    }


    @Test
    public void statusTest() {
        byte[] data = new byte[8];
        data[5] = (byte)0b11110111;
        FeedBackMessage m = new FeedBackMessage(data);
        assertEquals(0, m.current(1), kTestEpsilon);
        assertEquals(0, m.current(2), kTestEpsilon);
        assertEquals(0, m.current(3), kTestEpsilon);
        assertEquals(0, m.current(4), kTestEpsilon);
        assertEquals(0, m.totalCurrent(), kTestEpsilon);
        assertEquals(0, m.inputVoltage(), kTestEpsilon);
        assertEquals(0, m.firmware());

        assertEquals(new Status((byte)0b11110111), m.status());
    }
}
