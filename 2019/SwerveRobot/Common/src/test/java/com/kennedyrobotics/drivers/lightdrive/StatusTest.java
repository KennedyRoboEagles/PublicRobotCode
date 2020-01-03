package com.kennedyrobotics.drivers.lightdrive;

import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class StatusTest {

    @Test
    public void sanityTest() {
        final Status status = new Status((byte)0x00);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());

        assertThrows(IllegalArgumentException.class, () -> status.bankTrip(0));
        assertThrows(IllegalArgumentException.class, () -> status.bankTrip(5));
    }

    @Test
    public void enabledFlagTest() {
        Status status = new Status((byte)0x01);
        assertTrue(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());
    }

    @Test
    public void bankTripFlagTest() {
        // Bank 1
        Status status = new Status((byte)0x10);
        assertFalse(status.enabled());
        assertTrue(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());

        // Bank 2
        status = new Status((byte)0x20);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertTrue(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());

        // Bank 3
        status = new Status((byte)0x40);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertTrue(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());

        // Bank 4
        status = new Status((byte)0x80);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertTrue(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());
    }

    @Test
    public void modeTest() {
        // No signal
        Status status = new Status((byte)0b00000000);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kNoSignal, status.mode());

        // PWM
        status = new Status((byte)0b00000010);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kPWM, status.mode());

        // CAN
        status = new Status((byte)0b00000100);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kCAN, status.mode());

        // Serial
        status = new Status((byte)0b00000110);
        assertFalse(status.enabled());
        assertFalse(status.bankTrip(1));
        assertFalse(status.bankTrip(2));
        assertFalse(status.bankTrip(3));
        assertFalse(status.bankTrip(4));
        assertEquals(Mode.kSerial, status.mode());
    }
}
