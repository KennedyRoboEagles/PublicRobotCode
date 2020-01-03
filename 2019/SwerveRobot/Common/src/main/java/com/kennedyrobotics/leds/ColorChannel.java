package com.kennedyrobotics.leds;

/**
 * LED Color channel 
 */
public interface ColorChannel {

    /**
     * Set channel to the given color
     * @param color Color to set
     */
    void set(Color color); 

    /**
     * Set channel to the color at the given brightness 
     * @param color Color to set
     * @param brightness Color brightness from 0.0 to 1.0
     */
    void set(Color color, double brightness); 
}