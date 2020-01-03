package com.kennedyrobotics.swerve;


import com.kennedyrobotics.swerve.kennedy.SwerveCommand;
import com.kennedyrobotics.swerve.kennedy.SwerveDriveHelper;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;


public class SwerveDriveHelperTest {
    public static final double kTestEpsilon = 1e-5;


    @Test
    public void test() {
        SwerveDriveHelper k = new SwerveDriveHelper(30, 30);
     
        SwerveCommand state = k.inverseKinmatics(1.0, 0, 0);
        Assertions.assertEquals(1, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.frontRight.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.backLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(0.0, 0, 0);
        Assertions.assertEquals(0, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(0, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.frontRight.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.backLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(0.0, 0, 1);
        Assertions.assertEquals(1, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(Math.PI/4.0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(3*Math.PI/4.0, state.frontRight.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(-Math.PI/4.0, state.backLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(-3*Math.PI/4.0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(0.0, 0, -1);
        Assertions.assertEquals(1, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(-3*Math.PI/4.0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(-Math.PI/4.0, state.frontRight.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(3*Math.PI/4.0, state.backLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(Math.PI/4.0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(1, 1, 0);
        Assertions.assertEquals(1, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(1, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(Math.PI/4.0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(Math.PI/4.0, state.frontRight.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(Math.PI/4.0, state.backLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(Math.PI/4.0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(0.5, 0.5, 0.5);
        Assertions.assertEquals(1, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0.717438935, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(0.717438935, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0.171572875, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(Math.PI/4.0, state.frontLeft.angle.getRadians(), kTestEpsilon);
        Assertions.assertEquals(80.3*Math.PI/180.0, state.frontRight.angle.getRadians(), 0.01);
        Assertions.assertEquals(9.7*Math.PI/180.0, state.backLeft.angle.getRadians(), 0.01);
        Assertions.assertEquals(Math.PI/4.0, state.backRight.angle.getRadians(), kTestEpsilon);

        state = k.inverseKinmatics(6.10E-05, -0.010314941, 0.0);
        Assertions.assertEquals(0.010315122, state.frontLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0.010315122, state.frontRight.demand, kTestEpsilon);
        Assertions.assertEquals(0.010315122, state.backLeft.demand, kTestEpsilon);
        Assertions.assertEquals(0.010315122, state.backRight.demand, kTestEpsilon);

        Assertions.assertEquals(-89.7*Math.PI/180.0, state.frontLeft.angle.getRadians(), 0.01);
        Assertions.assertEquals(-89.7*Math.PI/180.0, state.frontRight.angle.getRadians(), 0.01);
        Assertions.assertEquals(-89.7*Math.PI/180.0, state.backLeft.angle.getRadians(), 0.01);
        Assertions.assertEquals(-89.7*Math.PI/180.0, state.backRight.angle.getRadians(), 0.01);

    }
}