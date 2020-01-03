package com.kennedyrobotics.leds;

/**
 * 
 */
public class Color {

    public static final Color RED = new Color(255, 0, 0);
    public static final Color GREEN = new Color(0, 255, 0);
    public static final Color BLUE = new Color(0, 0, 255);
    public static final Color TEAL = new Color(0, 255, 255);
    public static final Color YELLOW = new Color(255, 255, 0);
    public static final Color PURPLE = new Color(255, 0, 255);
    public static final Color WHITE = new Color(255, 255, 255);
    public static final Color OFF = new Color(0, 0, 0);

    private int red_;
    private int green_;
    private int blue_;

    /**
     * @todo
     */
    public Color() {
        this(0, 0, 0);
    }

    /**
     * @todo
     * @param r red channel values 0-255
     * @param g green channel values 0-255
     * @param b blue channel values 0-255
     */
    public Color(int r, int g, int b) {
        this.blue(b);
        this.green(g);
        this.red(r);
    }


    /**
     * Red color channel values: 0 to 255
     */
    public int red() {
        return red_;
    }

    /**
     * Green color channel values: 0 to 255
     */
    public int green() {
        return green_;
    }

    /**
     * Blue color channel values: 0 to 255
     */
    public int blue() {
        return blue_;
    }

    /**
     * Set red channel
     * @param r Value between 0-255
     */
    public void red(int r) {
        red_ = Math.max(0, Math.min(r, 255));
    }

    /**
     * Set green channel
     * @param r Value between 0-255
     */
    public void green(int g) {
        green_ = Math.max(0, Math.min(g, 255));
    }

    /**
     * Set blue channel
     * @param r Value between 0-255
     */
    public void blue(int b) {
        blue_ = Math.max(0, Math.min(b, 255));
    }
}