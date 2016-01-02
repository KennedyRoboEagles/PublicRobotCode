package org.nowireless.frc2015.tower.panels;

import javax.swing.JPanel;

import java.awt.GridLayout;
import java.math.RoundingMode;
import java.text.DecimalFormat;

import javax.swing.JLabel;
import javax.swing.JFormattedTextField;

import org.nowireless.vision.gui.JBooleanBox;

public class TowerStatPanel extends JPanel {

	private static final long serialVersionUID = 1L;

	private final DecimalFormat format = new DecimalFormat("###.##");

	private final JFormattedTextField formattedTextField;
	private final JFormattedTextField formattedTextField_1;
	private final JFormattedTextField formattedTextField_2;
	private final JBooleanBox booleanBox;
	private final JFormattedTextField formattedTextField_3;
	private final JFormattedTextField formattedTextField_4;
	private final JFormattedTextField formattedTextField_5;
	/**
	 * Create the panel.
	 */
	public TowerStatPanel() {
		format.setRoundingMode(RoundingMode.UNNECESSARY);
		
		setLayout(new GridLayout(0, 2, 0, 0));
		
		JLabel lblPosition = new JLabel("Position");
		add(lblPosition);
		
		formattedTextField = new JFormattedTextField();
		add(formattedTextField);
		
		JLabel lblState = new JLabel("State");
		add(lblState);
		
		formattedTextField_1 = new JFormattedTextField();
		add(formattedTextField_1);
		
		JLabel lblForceVoltage = new JLabel("Force Voltage");
		add(lblForceVoltage);
		
		formattedTextField_2 = new JFormattedTextField();
		add(formattedTextField_2);
		
		JLabel lblAtPosition = new JLabel("At Position");
		add(lblAtPosition);
		
		booleanBox = new JBooleanBox();
		add(booleanBox);
		
		JLabel lblSetpoint = new JLabel("Setpoint");
		add(lblSetpoint);
		
		formattedTextField_3 = new JFormattedTextField();
		add(formattedTextField_3);
		
		JLabel lblCurrentPosition = new JLabel("Current Position");
		add(lblCurrentPosition);
		
		formattedTextField_4 = new JFormattedTextField();
		add(formattedTextField_4);
		
		JLabel lblDelta = new JLabel("Delta");
		add(lblDelta);
		
		formattedTextField_5 = new JFormattedTextField();
		add(formattedTextField_5);
		
		this.updateStats("Unknown Position", "Unknown State", 0.0, false, 0.0, 0.0, 0.0);
	}

	/*
	 * NOT THREAD SAFE!
	 */
	public void updateStats(String position, String state, double forceVoltage, boolean atPosition, double setpoint, double currentPosition, double delta) {
		this.formattedTextField.setText(position);
		this.formattedTextField_1.setText(state);
		this.formattedTextField_2.setText(this.formatDouble(forceVoltage));
		this.booleanBox.set(atPosition);
		this.formattedTextField_3.setText(this.formatDouble(setpoint));
		this.formattedTextField_4.setText(this.formatDouble(currentPosition));
		this.formattedTextField_5.setText(this.formatDouble(delta));
		this.repaint();
	}
	
	protected String formatDouble(double val) {
		return Double.toString(val);
	}
}
