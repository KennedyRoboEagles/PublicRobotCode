package org.nowireless.frc2015.tower;

import javax.swing.SwingUtilities;

import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;

import org.nowireless.frc2015.tower.panels.TowerPanel;
import org.nowireless.frc2015.tower.panels.TowerUIPanel;

@SuppressWarnings("serial")
public class Tower extends Widget {
	public static final DataType[] TYPES = {TowerType.get()};
	private TowerUIPanel towerUIPanel;
	private ITable table;
	
	private ITableListener listener = new ITableListener() {
		 volatile boolean running = false;
		
		@Override
		public void valueChanged(ITable arg0, String arg1, Object arg2, boolean arg3) {
			//System.out.println("New INFO!");
			 if (running) {
	                return;
	         }
			 
			 running = true;
			 SwingUtilities.invokeLater(new Runnable() {
				
				@Override
				public void run() {
					synchronized (table) {
						String position 		= table.getString("Position", "Default Position");
						String state			= table.getString("State", "Default State");
						double forceVoltage		= table.getNumber("Force Voltage", 0.0);
						boolean atPosition 		= table.getBoolean("At Position", false);
						double setpoint 		= table.getNumber("Setpoint", 0.0);
						double currentPosition	= table.getNumber("Current Position", 0.0);
						double delta 			= table.getNumber("Delta", 0.0);
						towerUIPanel.getStatPanel().updateStats(position, state, forceVoltage, atPosition, setpoint, currentPosition, delta);
						
						boolean upper = table.getBoolean("Upper Limit", false);
						boolean lower = table.getBoolean("Lower Limit", false);
						double height = currentPosition;
						towerUIPanel.getTowerPanel().updateTower(upper, lower, height, setpoint);
						
						running = false;
					}
				}
			});
		}
	};
	
	public Tower() {
		towerUIPanel = new TowerUIPanel();
		this.setPreferredSize(towerUIPanel.getPreferredSize());
		add(towerUIPanel);
	}
		
	@Override
	public void propertyChanged(Property arg0) {
		// TODO Auto-generated method stub
	}

	@Override
	public void setValue(Object value) {
		if (table != null) {
			table.removeTableListener(listener);
		}
		table = (ITable) value;
		table.addTableListener(listener, true);

	    revalidate();
	    repaint();
	}

	@Override
	public void init() {
		towerUIPanel.getStatPanel().updateStats("Default Position", "Default State", 0.0, false, 0.0, 0.0, 0.0);
		towerUIPanel.getTowerPanel().updateTower(false, false, 0.0, TowerPanel.TOWER_HIGH);
	}
}
