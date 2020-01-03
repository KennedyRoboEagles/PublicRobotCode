package com.kennedyrobotics.drivers;

import edu.wpi.first.wpilibj.I2C;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;

/**
 * Implementation of the RevRobotics Color Sensor V2
 *
 * From: https://github.com/BadRobots1014/2019_Shepard/blob/master/src/main/java/frc/robot/driver/RevColorSensorV2.java
 *
 * @see "http://www.revrobotics.com/content/docs/TMD3782_v2.pdf"
 */
public class RevColorSensorV2 extends I2C implements AutoCloseable {
    /* ---------------------------- READ/WRITE ---------------------------- */

    private final static int ENABLE = 0x00; // Enables states and interrupts
    private final static int ATIME = 0x01; // RGBC time
    private final static int WTIME = 0x03; // Wait time

    /**
     * Clear Channel Interrupt Threshold Registers
     */
    private final static int AILTL = 0x04; // Clear interrupt low threshold low byte
    private final static int AILTH = 0x05; // Clear interrupt low threshold high byte
    private final static int AIHTL = 0x06; // Clear interrupt high threshold low byte
    private final static int AIHTH = 0x07; // Clear interrupt high threshold high byte

    /**
     * Proximity Interrupt Threshold Registers
     */
    private final static int PILTL = 0x08; // Proximity interrupt low threshold low byte
    private final static int PILTH = 0x09; // Proximity interrupt low threshold high byte
    private final static int PIHTL = 0x0A; // Proximity interrupt high threshold low byte
    private final static int PIHTH = 0x0B; // Proximity interrupt high threshold high byte

    private final static int PERS = 0x0C; // Interrupt persistence filters
    private final static int CONFIG = 0x0D; // Configuration
    private final static int PPULSE = 0x0E; // Proximity pulse count
    private final static int CONTROL = 0x0F; // Gain control

    /* ----------------------------- READ ONLY ----------------------------- */

    private final static int REVISION = 0x11; // Die revision number
    private final static int ID = 0x12; // Device ID
    private final static int STATUS = 0x13; // Device status

    /**
     * RGBC Data Registers
     */
    private final static int CDATAL = 0x14; // Clear ADC low data register
    private final static int CDATAH = 0x15; // Clear ADC high data register
    private final static int RDATAL = 0x16; // Red ADC low data register
    private final static int RDATAH = 0x17; // Red ADC high data register
    private final static int GDATAL = 0x18; // Green ADC low data register
    private final static int GDATAH = 0x19; // Green ADC high data register
    private final static int BDATAL = 0x1A; // Blue ADC low data register
    private final static int BDATAH = 0x1B; // Blue ADC high data register

    /**
     * Proximity Data Registers
     */
    private final static int PDATAL = 0x1C; // Proximity ADC low data register
    private final static int PDATAH = 0x1D; // Proximity ADC high data register

    /**
     * Enable Register Fields
     */
    private final static int PIEN = 1 << 5; // Proximity Interrupt Enable
    private final static int AIEN = 1 << 4; // Ambient Light Sensor Interupt Enable
    private final static int WEN = 1 << 3; // Wait Enable
    private final static int PEN = 1 << 2; // Proximity Enable
    private final static int AEN = 1 << 1; // ADC Enable
    private final static int PON = 1; // Power ON

    /**
     * Command Register Fields
     */
    private final static int COMMAND = 1 << 7; // Specified register address
    private final static int MULTI_BYTE_BIT = 1 << 5; // Signals device to read successive bytes

    /**
     * Instance Variables
     */
    private final ByteBuffer byteBuffer = ByteBuffer.allocate(8);
    private final double integrationTime = 10;

    /**
     * Creates a new instance of a RevColorSensorV2 and prepares it for operation
     */
    public RevColorSensorV2(Port port) {
        super(port, 0x39);
        byteBuffer.order(ByteOrder.LITTLE_ENDIAN);

        init();
    }

    public void init() {
        write(COMMAND | ENABLE, PON | AEN | PEN);
        write(COMMAND | ATIME, (int) (256 - integrationTime / 2.38));
        write(COMMAND | PPULSE, 0b1111);
        write(COMMAND | CONTROL, 0b0010_0010);
    }

    /**
     * Read the red, green, blue, and alpha values from the sensor
     */
    public short[] getRGBA() {
        byteBuffer.clear();
        read(COMMAND | MULTI_BYTE_BIT | CDATAL, 8, byteBuffer);

        short alpha = (short) (asUnsignedShort(byteBuffer.getShort(0)) / 20);
        short red = (short) (asUnsignedShort(byteBuffer.getShort(2)) / 20);
        short green = (short) (asUnsignedShort(byteBuffer.getShort(4)) / 20);
        short blue = (short) (asUnsignedShort(byteBuffer.getShort(6)) / 20);

        return new short[] {red, green, blue, alpha};
    }

    /**
     * Read the current proximity value from the sensor
     *
     * @return the proximity to the closest opaque object
     */
    public short getProximity() {
        return readShort(PDATAL);
    }

    /**
     * Read the current gain control value of the sensor
     *
     * @return the current gain control of the sensor
     */
    public byte getControl() {
        return readByte(CONTROL);
    }

    /**
     * Read the value of the {@link #STATUS} register of the sensor
     *
     * @return the current status of the sensor
     */
    public int getStatus() {
        return readByte(STATUS);
    }

    /**
     * Convience method that reads 1 byte from the given register address
     *
     * @param register the register address of the byte that is to be read
     * @return the byte that was read
     */
    private byte readByte(int register) {
        byteBuffer.clear();
        read(COMMAND | register, 1, byteBuffer);
        return byteBuffer.get(0);
    }

    /**
     * Convience method that reads 2 bytes starting at the given register address and converts them
     * to a short
     *
     * @param register the register address of the first byte that is to be read
     * @return the short equivalent of the 2 bytes that were read
     */
    public short readShort(int register) {
        byteBuffer.clear();
        read(COMMAND | MULTI_BYTE_BIT | register, 2, byteBuffer);
        return asUnsignedShort(byteBuffer.getShort(0));
    }

    private short asUnsignedShort(short signedShort) {
        if (signedShort < 0)
            return signedShort += 1 << 16;
        else
            return signedShort;
    }
}