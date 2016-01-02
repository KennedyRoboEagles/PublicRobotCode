package org.nowireless.frc2015.tower.panels;

import java.awt.Dimension;

import javax.swing.JPanel;
import javax.swing.SpringLayout;

public class TowerUIPanel extends JPanel {

	private static final long serialVersionUID = 1L;
	private TowerPanel towerPanel;
	private TowerStatPanel statPanel;
	
	public TowerPanel getTowerPanel() {
		return this.towerPanel;
	}
	
	public TowerStatPanel getStatPanel() {
		return this.statPanel;
	}
	
	/**
	 * Create the panel.
	 */
	public TowerUIPanel() {
		this.setPreferredSize(new Dimension(681, 655));
		SpringLayout springLayout = new SpringLayout();
		setLayout(springLayout);
		
		statPanel = new TowerStatPanel();
		springLayout.putConstraint(SpringLayout.NORTH, statPanel, 10, SpringLayout.NORTH, this);
		springLayout.putConstraint(SpringLayout.WEST, statPanel, 10, SpringLayout.WEST, this);
		springLayout.putConstraint(SpringLayout.SOUTH, statPanel, 200, SpringLayout.NORTH, this);
		springLayout.putConstraint(SpringLayout.EAST, statPanel, 275, SpringLayout.WEST, this);
		add(statPanel);
		
		towerPanel = new TowerPanel();
		springLayout.putConstraint(SpringLayout.NORTH, towerPanel, 0, SpringLayout.NORTH, this);
		springLayout.putConstraint(SpringLayout.WEST, towerPanel, 16, SpringLayout.EAST, statPanel);
		springLayout.putConstraint(SpringLayout.EAST, towerPanel, 365, SpringLayout.EAST, statPanel);
		add(towerPanel);
	}
}
