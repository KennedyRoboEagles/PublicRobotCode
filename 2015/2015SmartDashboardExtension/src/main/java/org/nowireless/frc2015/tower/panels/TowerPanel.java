package org.nowireless.frc2015.tower.panels;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.util.Map.Entry;

import javax.swing.JPanel;
import javax.swing.SpringLayout;
import javax.swing.JLabel;

import org.nowireless.frc2015.tower.TowerPosition;
import org.nowireless.vision.gui.JBooleanBox;

public class TowerPanel extends JPanel {

	private static final Font FONT = new Font(Font.SERIF, Font.BOLD, 18);
	private static final long serialVersionUID = 1L;
	private final static int TOWER_RECT_Y = 40;
	private final static int TOWER_RECT_LENGTH = 560;
	private final static double TOWER_LOW = 9;
	public final static double TOWER_HIGH = 61.5;
	private final static double TOWER_OFFSET = 9.5;
	
	private volatile double towerHeight;
	private volatile double towerSetpoint;
	
	private final JBooleanBox booleanBox;
	private final JBooleanBox booleanBox_1;
	
	/**
	 * Create the panel.
	 */
	public TowerPanel() {
		this.setPreferredSize(new Dimension(175, 640));
		SpringLayout springLayout = new SpringLayout();
		setLayout(springLayout);
		
		JLabel lblUpperLimit = new JLabel("Upper Limit");
		springLayout.putConstraint(SpringLayout.NORTH, lblUpperLimit, 10, SpringLayout.NORTH, this);
		springLayout.putConstraint(SpringLayout.WEST, lblUpperLimit, 10, SpringLayout.WEST, this);
		add(lblUpperLimit);
		
		booleanBox = new JBooleanBox();
		springLayout.putConstraint(SpringLayout.NORTH, booleanBox, -5, SpringLayout.NORTH, lblUpperLimit);
		springLayout.putConstraint(SpringLayout.WEST, booleanBox, 6, SpringLayout.EAST, lblUpperLimit);
		springLayout.putConstraint(SpringLayout.SOUTH, booleanBox, 5, SpringLayout.SOUTH, lblUpperLimit);
		springLayout.putConstraint(SpringLayout.EAST, booleanBox, -10, SpringLayout.EAST, this);
		add(booleanBox);
		
		JLabel lblBottomLimit = new JLabel("Bottom Limit");
		springLayout.putConstraint(SpringLayout.WEST, lblBottomLimit, 10, SpringLayout.WEST, this);
		springLayout.putConstraint(SpringLayout.SOUTH, lblBottomLimit, -10, SpringLayout.SOUTH, this);
		add(lblBottomLimit);
		
		booleanBox_1 = new JBooleanBox();
		springLayout.putConstraint(SpringLayout.NORTH, booleanBox_1, -5, SpringLayout.NORTH, lblBottomLimit);
		springLayout.putConstraint(SpringLayout.WEST, booleanBox_1, 5, SpringLayout.EAST, lblBottomLimit);
		springLayout.putConstraint(SpringLayout.SOUTH, booleanBox_1, 5, SpringLayout.SOUTH, lblBottomLimit);
		springLayout.putConstraint(SpringLayout.EAST, booleanBox_1, -10, SpringLayout.EAST, this);
		add(booleanBox_1);
		//this.repaint();
		this.towerHeight = TOWER_HIGH / 2.0;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		
		//Draw the tower
		g.setColor(Color.BLACK);
		g.fillRect(10, TOWER_RECT_Y, 15, TOWER_RECT_LENGTH);
		g.fillRect(150, TOWER_RECT_Y, 15, TOWER_RECT_LENGTH);
	
		//Draw the set point;
		int setpointLoc = this.locationInchesToPixel(this.towerSetpoint);
		g.setColor(Color.RED);
		g.fillRect(25, setpointLoc, 125, 10);
		
		//Draw the current position 
		int loc = this.locationInchesToPixel(this.towerHeight);
		g.setColor(Color.ORANGE);
		g.fillRect(25, loc, 125, 10);
		
		//Draw Positions
		g.setColor(Color.BLACK);
		g.setFont(FONT);
		for(Entry<String, Double> entry : TowerPosition.GetPositions()) {
			int position = this.locationInchesToPixel(entry.getValue());
			g.drawString(entry.getKey(), 170, position);
		}
	}
	
	private int locationInchesToPixel(double inches) {
		double pixelsPerInch = 1.0 / ((TOWER_HIGH - TOWER_LOW) / (TOWER_RECT_LENGTH));
		int loc = (int) ( (pixelsPerInch * (inches - TOWER_OFFSET)));
		if(loc < 0) {
			loc = 0;
		} else if (loc > TOWER_RECT_LENGTH) {
			loc = TOWER_RECT_LENGTH;
		}
		
		loc = TOWER_RECT_LENGTH - loc + TOWER_RECT_Y - 5;
		return loc;
	}
	
	public void updateTower(boolean upper, boolean lower, double height, double setpoint) {
		this.booleanBox.set(upper);
		this.booleanBox_1.set(lower);
		this.towerHeight = height;
		this.towerSetpoint = setpoint;
		this.repaint();
	}
}
