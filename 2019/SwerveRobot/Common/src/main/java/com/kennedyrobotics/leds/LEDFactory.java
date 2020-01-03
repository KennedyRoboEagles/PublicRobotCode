package com.kennedyrobotics.leds;

import com.ctre.phoenix.CANifier;
import com.kennedyrobotics.exceptions.TodoException;

public class LEDFactory {

    /**
     * 
     * @param c
     * @return
     */
    public ColorChannel createCANifierColor(CANifier c) {
        throw new TodoException();
    }

    /**
     * 
     * @param c
     * @param channelId
     * @return
     */
    public LEDChannel createCANifierLED(CANifier c, int channelId) {
        throw new TodoException();
    }


    /**
     * Create new Ghost ColorChannel instance
     * @return ghost color channel
     */
    public ColorChannel createGhostColor() {
        return new ColorChannel(){
        
            @Override
            public void set(Color color, double brightness) {}
        
            @Override
            public void set(Color color) {}
        };
    }

    /**
     * Create new Ghost LEDChannel instance
     * @return ghost led channel
     */
    public LEDChannel createGhostLED() {
        return new LEDChannel(){
        
            @Override
            public void set(double brightness) {}
        };
    }
}