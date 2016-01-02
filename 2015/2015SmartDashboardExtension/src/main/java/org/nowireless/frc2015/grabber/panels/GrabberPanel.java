package org.nowireless.frc2015.grabber.panels;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.JPanel;

public class GrabberPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private static final int GRABBER_LENGTH = 700;
	private static final double GRABBER_MAX_OPEN_DISTANCE = 28.5;
	private static final int centerX = 10 + GRABBER_LENGTH / 2;
	
	private volatile double setpoint = 20;
	private volatile double position = 10;
	
	/**
	 * Create the panel.
	 */
	public GrabberPanel() {
		this.setPreferredSize(new Dimension(747, 200));
	}

	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.setColor(Color.BLACK);
		
		//Draw Bars
		g.fillRect(10, 10, GRABBER_LENGTH, 15);
		g.fillRect(10, 125, GRABBER_LENGTH, 15);
		
		//Draw Center Line
		g.drawLine(centerX, 10, centerX, 125);
		
		//Draw Setpoint lines
		g.setColor(Color.RED);
		g.fillRect(this.inchToPixelLeftX(this.setpoint), 25, 14, 100);
		g.fillRect(this.inchToPixelRightX(this.setpoint), 25, 14, 100);
		
		//Draw Positon lines
		g.setColor(Color.ORANGE);
		g.fillRect(this.inchToPixelLeftX(this.position), 25, 14, 100);
		g.fillRect(this.inchToPixelRightX(this.position), 25, 14, 100);
	}
	
	private int inchToPixelLeftX(double inch) {
		inch = inch / 2.0;
		double pixelPerInch = GRABBER_LENGTH / GRABBER_MAX_OPEN_DISTANCE;
		int loc = (int)(pixelPerInch * inch);
		return loc + centerX;
	}
	
	private int inchToPixelRightX(double inch) {
		inch = inch / 2.0;
		double pixelPerInch = GRABBER_LENGTH / GRABBER_MAX_OPEN_DISTANCE;
		int loc = (int)(pixelPerInch * inch);
		return centerX - loc;
	}
	
	public void update(double position, double setpoint) {
		this.position = position;
		this.setpoint = setpoint;
		repaint();
	}
}
