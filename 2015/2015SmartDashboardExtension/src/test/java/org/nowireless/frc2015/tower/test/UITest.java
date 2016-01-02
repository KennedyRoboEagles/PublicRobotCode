package org.nowireless.frc2015.tower.test;

import java.awt.EventQueue;

import javax.swing.JFrame;

import java.awt.BorderLayout;

import org.nowireless.frc2015.tower.panels.TowerUIPanel;

public class UITest {

	private JFrame frame;

	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					UITest window = new UITest();
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public UITest() {
		initialize();
	}

	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		frame.setBounds(100, 100, 670, 670);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		TowerUIPanel towerUIPanel = new TowerUIPanel();
		frame.getContentPane().add(towerUIPanel, BorderLayout.CENTER);
	}

}
