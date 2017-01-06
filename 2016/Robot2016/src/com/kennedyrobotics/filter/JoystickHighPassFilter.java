package com.kennedyrobotics.filter;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PIDSource;
import edu.wpi.first.wpilibj.PIDSourceType;
import edu.wpi.first.wpilibj.filters.LinearDigitalFilter;

public class JoystickHighPassFilter {

	private final LinearDigitalFilter m_xAxis;
	private final LinearDigitalFilter m_yAxis;
	
	private final Joystick m_joy;
	
	public JoystickHighPassFilter(Joystick joy, double timeConstant, double period) {
		this.m_joy = joy;
		
		m_xAxis = LinearDigitalFilter.highPass(new PIDSource() {
			@Override public PIDSourceType getPIDSourceType() { return PIDSourceType.kRate; }
			@Override public void setPIDSourceType(PIDSourceType pidSource) {}
			@Override public double pidGet() {
				return m_joy.getX();
			}
			
		}, timeConstant, period);
		
		m_yAxis = LinearDigitalFilter.highPass(new PIDSource() {
			@Override public PIDSourceType getPIDSourceType() { return PIDSourceType.kRate; }
			@Override public void setPIDSourceType(PIDSourceType pidSource) {}
			@Override public double pidGet() {
				return m_joy.getY();
			}

		}, timeConstant, period);
	}
	
	/**
	 * Calculate next values
	 */
	public void calculate() {
		m_xAxis.pidGet();
		m_yAxis.pidGet();
	}
	
	/**
	 * Reset the internal filters
	 */
	public void reset() {
		m_xAxis.reset();
		m_yAxis.reset();
	}
	
	public double getX() {
		return m_xAxis.get();
	}
	
	public double getY() {
		return m_yAxis.get();
	}
}
