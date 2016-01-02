package org.nowireless.frc2015.grabber.panels;

import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.SpringLayout;

public class GrabberUIPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private final GrabberStatPanel grabberStatPanel;
	private final GrabberPanel grabberPanel;
	
	public GrabberStatPanel GetStatPanel() {
		return this.grabberStatPanel;
	}
	
	public GrabberPanel GetGrabberPanel() {
		return this.grabberPanel;
	}
	
	/**
	 * Create the panel.
	 */
	public GrabberUIPanel() {
		setPreferredSize(new Dimension(767, 439));
		SpringLayout springLayout = new SpringLayout();
		setLayout(springLayout);
		
		grabberStatPanel = new GrabberStatPanel();
		springLayout.putConstraint(SpringLayout.NORTH, grabberStatPanel, 10, SpringLayout.NORTH, this);
		springLayout.putConstraint(SpringLayout.WEST, grabberStatPanel, 10, SpringLayout.WEST, this);
		add(grabberStatPanel);
		
		grabberPanel = new GrabberPanel();
		springLayout.putConstraint(SpringLayout.NORTH, grabberPanel, 6, SpringLayout.SOUTH, grabberStatPanel);
		springLayout.putConstraint(SpringLayout.WEST, grabberPanel, 0, SpringLayout.WEST, grabberStatPanel);
		add(grabberPanel);
	}
}
