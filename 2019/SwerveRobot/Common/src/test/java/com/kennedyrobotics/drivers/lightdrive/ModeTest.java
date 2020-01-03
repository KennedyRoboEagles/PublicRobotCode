package com.kennedyrobotics.drivers.lightdrive;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class ModeTest {

    @Test
    public void test() {
        assertEquals(Mode.kNoSignal, Mode.from(0));
        assertEquals(Mode.kPWM, Mode.from(1));
        assertEquals(Mode.kCAN, Mode.from(2));
        assertEquals(Mode.kSerial, Mode.from(3));

        assertThrows(IllegalArgumentException.class, () -> {
            Mode.from(-1);
        });
        assertThrows(IllegalArgumentException.class, () -> {
            Mode.from(4);
        });
    }
}
