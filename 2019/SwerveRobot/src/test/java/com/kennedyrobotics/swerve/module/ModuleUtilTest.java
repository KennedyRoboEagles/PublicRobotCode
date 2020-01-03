package com.kennedyrobotics.swerve.module;

import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;


public class ModuleUtilTest {
    public static final double kTestEpsilon = 1e-5;

    @Test
    public void testFindClosestAngle() {
        assertEquals(0,
                ModuleUtil.findClosestAngle(0, 0),
                kTestEpsilon
        );

        assertEquals(Math.toRadians(0),
            ModuleUtil.findClosestAngle(Math.toRadians(0), Math.toRadians(0)),
            kTestEpsilon
        );

        assertEquals(Math.toRadians(30),
            ModuleUtil.findClosestAngle(Math.toRadians(0), Math.toRadians(30)),
            kTestEpsilon
        );

        assertEquals(Math.toRadians(-30),
            ModuleUtil.findClosestAngle(Math.toRadians(0), Math.toRadians(-30)),
            kTestEpsilon
        );

        
    }

}