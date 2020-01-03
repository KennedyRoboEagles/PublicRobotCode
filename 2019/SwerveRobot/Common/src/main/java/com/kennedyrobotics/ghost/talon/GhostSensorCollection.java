package com.kennedyrobotics.ghost.talon;

import com.ctre.phoenix.ErrorCode;
import com.ctre.phoenix.motorcontrol.SensorCollection;
import com.ctre.phoenix.motorcontrol.can.BaseMotorController;

public class GhostSensorCollection extends SensorCollection {

    public GhostSensorCollection(BaseMotorController mc) {
        super(mc);
    }

    @Override
    public int getAnalogIn() {
        return 0;
    }

    @Override
    public ErrorCode setAnalogPosition(int newPosition, int timeoutMs) {
        return ErrorCode.OK;
    }

    @Override
    public int getAnalogInRaw() {
        return 0;
    }

    @Override
    public int getAnalogInVel() {
        return 0;
    }

    @Override
    public int getQuadraturePosition() {
        return 0;
    }

    @Override
    public ErrorCode setQuadraturePosition(int newPosition, int timeoutMs) {
        return ErrorCode.OK;
    }

    @Override
    public int getQuadratureVelocity() {
        return 0;
    }

    @Override
    public ErrorCode syncQuadratureWithPulseWidth(int bookend0, int bookend1, boolean bCrossZeroOnInterval) {
        return ErrorCode.OK;
    }

    @Override
    public ErrorCode syncQuadratureWithPulseWidth(int bookend0, int bookend1, boolean bCrossZeroOnInterval, int offset, int timeoutMs) {
        return ErrorCode.OK;
    }

    @Override
    public int getPulseWidthPosition() {
        return 0;
    }

    @Override
    public ErrorCode setPulseWidthPosition(int newPosition, int timeoutMs) {
        return ErrorCode.OK;
    }

    @Override
    public int getPulseWidthRiseToFallUs() {
        return 0;
    }

    @Override
    public int getPulseWidthRiseToRiseUs() {
        return 0;
    }

    @Override
    public boolean getPinStateQuadA() {
        return false;
    }

    @Override
    public boolean getPinStateQuadB() {
        return false;
    }

    @Override
    public boolean getPinStateQuadIdx() {
        return false;
    }

    @Override
    public boolean isFwdLimitSwitchClosed() {
        return false;
    }

    @Override
    public boolean isRevLimitSwitchClosed() {
        return false;
    }
}
