package com.kennedyrobotics.drivers.lightdrive;

import com.kennedyrobotics.leds.Color;

public interface LightDrive {

    /**
     * Set light drive color channel to the specified color
     * @param colorChannel channel between 1 to 4
     * @param color color to display
     */
    void setColor(int colorChannel, Color color);

    /**
     * Set light drive color channel to the specified color and brightness
     * @param colorChannel color channel between 1 to 4
     * @param color color to display
     * @param brightness color brightness
     */
    void setColor(int colorChannel, Color color, double brightness);

    /**
     * Set single led channel on light drive to the specified brightness
     * @param channel led channel between 1 and 12
     * @param brightness led brightness
     */
    void setLed(int channel, double brightness);

    /**
     * Push latest commands to LightDrive
     */
    void update();

    /**
     * Light Drive feedback
     * @return feedback
     */
    FeedBackMessage feedback();
}
