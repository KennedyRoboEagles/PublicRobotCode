package org.nowireless.frc2015.grabber.panels;

import javax.swing.JPanel;

import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JLabel;
import javax.swing.JFormattedTextField;

import org.nowireless.vision.gui.JBooleanBox;

public class GrabberStatPanel extends JPanel {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private final JFormattedTextField formattedTextField;
	private final JFormattedTextField formattedTextField_1;
	private final JFormattedTextField formattedTextField_5;
	private final JFormattedTextField formattedTextField_3;
	private final JFormattedTextField formattedTextField_4;
	private final JFormattedTextField formattedTextField_2;
	private final JBooleanBox booleanBox;

	/**
	 * Create the panel.
	 */
	public GrabberStatPanel() {
		setPreferredSize(new Dimension(747, 207));
		setLayout(new GridLayout(0, 4, 0, 0));
		
		JLabel lblState = new JLabel("State");
		add(lblState);
		
		formattedTextField = new JFormattedTextField();
		add(formattedTextField);
		
		JLabel lblPosition = new JLabel("Position");
		add(lblPosition);
		
		formattedTextField_1 = new JFormattedTextField();
		add(formattedTextField_1);
		
		JLabel lblCurrentDraw = new JLabel("Current Draw");
		add(lblCurrentDraw);
		
		formattedTextField_5 = new JFormattedTextField();
		add(formattedTextField_5);
		
		JLabel lblSetpoint = new JLabel("Setpoint");
		add(lblSetpoint);
		
		formattedTextField_3 = new JFormattedTextField();
		add(formattedTextField_3);
		
		JLabel lblCurrnetPosition = new JLabel("Currnet Position");
		add(lblCurrnetPosition);
		
		formattedTextField_4 = new JFormattedTextField();
		add(formattedTextField_4);
		
		JLabel lblDelta = new JLabel("Delta");
		add(lblDelta);
		
		formattedTextField_2 = new JFormattedTextField();
		add(formattedTextField_2);
		
		JLabel lblIsDone = new JLabel("Is Done");
		add(lblIsDone);
		
		booleanBox = new JBooleanBox();
		add(booleanBox);

	}
	
	/*
	 * Not Thread SAFE!
	 */
	public void updateState(String state, String position, double currentDraw, double setpoint, double currentPosition, double delta, boolean isDone) {
		formattedTextField.setText(state);
		formattedTextField_1.setText(position);
		formattedTextField_5.setText(Double.toString(currentDraw));
		formattedTextField_3.setText(Double.toString(setpoint));
		formattedTextField_4.setText(Double.toString(currentDraw));
		formattedTextField_2.setText(Double.toString(delta));
		booleanBox.set(isDone);
	}
}
