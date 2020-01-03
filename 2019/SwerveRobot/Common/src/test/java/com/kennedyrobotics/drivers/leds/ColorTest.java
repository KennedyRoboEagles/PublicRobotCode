package com.kennedyrobotics.drivers.leds;

import static org.junit.jupiter.api.Assertions.*;

import com.kennedyrobotics.leds.Color;
import org.junit.jupiter.api.Test;

public class ColorTest {

    @Test
    public void test() {
        // Test constructors
        Color c = new Color();
        assertEquals(0, c.red());
        assertEquals(0, c.green());
        assertEquals(0, c.blue());

        c = new Color(10, 20, 30);
        assertEquals(10, c.red());
        assertEquals(20, c.green());
        assertEquals(30, c.blue());

        c = new Color(300, 400, 500);
        assertEquals(255, c.red());
        assertEquals(255, c.green());
        assertEquals(255, c.blue());

        // Test Setters and getters
        c = new Color();
        c.red(-100);
        assertEquals(0, c.red());
        c.red(0);
        assertEquals(0, c.red());
        c.red(128);
        assertEquals(128, c.red());
        c.red(255);
        assertEquals(255, c.red());
        c.red(300);
        assertEquals(255, c.red());

        c.blue(-100);
        assertEquals(0, c.blue());
        c.blue(0);
        assertEquals(0, c.blue());
        c.blue(128);
        assertEquals(128, c.blue());
        c.blue(255);
        assertEquals(255, c.blue());
        c.blue(300);
        assertEquals(255, c.blue());

        c.green(-100);
        assertEquals(0, c.green());
        c.green(0);
        assertEquals(0, c.green());
        c.green(128);
        assertEquals(128, c.green());
        c.green(255);
        assertEquals(255, c.green());
        c.green(300);
        assertEquals(255, c.green());

    }
}