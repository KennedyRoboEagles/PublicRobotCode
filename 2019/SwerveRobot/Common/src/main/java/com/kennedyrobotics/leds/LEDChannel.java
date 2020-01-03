package com.kennedyrobotics.leds;

/**
 * Single LED channel
 */
public interface LEDChannel {

    /**
     * Set channel's brightness 
     * @param brightness value between 0.0 to 1.0
     */
    void set(double brightness);
}