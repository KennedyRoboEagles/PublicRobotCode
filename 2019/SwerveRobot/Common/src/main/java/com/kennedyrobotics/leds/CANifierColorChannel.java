package com.kennedyrobotics.leds;

import com.ctre.phoenix.CANifier;
import com.ctre.phoenix.CANifier.LEDChannel;

/**
 * LED color channel on the CTRE CANifier.
 */
public class CANifierColorChannel implements ColorChannel {

    private final CANifier canifier_;

	/**
	 * Color channel on CANifier
	 *
	 * The CANifier only supports only 1 color channel.
	 * @param canifier CANifier instance
	 */
	public CANifierColorChannel(CANifier canifier) {
        canifier_ = canifier;
    }

	@Override
	public void set(Color color) {
        this.set(color, 1.0);
	}

	@Override
	public void set(Color color, double brightness) {
		double r = color.red() / 255.0 * brightness;
		double g = color.green() / 255.0 * brightness;
		double b = color.blue() / 255.0 * brightness;

		canifier_.setLEDOutput(r, LEDChannel.LEDChannelA);
		canifier_.setLEDOutput(g, LEDChannel.LEDChannelB);
		canifier_.setLEDOutput(b, LEDChannel.LEDChannelC);
	}
}