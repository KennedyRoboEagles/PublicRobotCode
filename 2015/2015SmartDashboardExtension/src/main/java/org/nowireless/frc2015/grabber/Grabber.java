package org.nowireless.frc2015.grabber;

import javax.swing.SwingUtilities;

import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.properties.Property;
import edu.wpi.first.smartdashboard.types.DataType;
import edu.wpi.first.wpilibj.tables.ITable;
import edu.wpi.first.wpilibj.tables.ITableListener;
import org.nowireless.frc2015.grabber.panels.GrabberUIPanel;

@SuppressWarnings("serial")
public class Grabber extends Widget {
	
	private final GrabberUIPanel grabberUIPanel;
	
	public Grabber() {
		grabberUIPanel = new GrabberUIPanel();
		setPreferredSize(grabberUIPanel.getPreferredSize());
		add(grabberUIPanel);
	}

	public static final DataType[] TYPES = {GrabberType.get()};
	private ITable table;
	
	private ITableListener listener = new ITableListener() {
		volatile boolean running = false;
		
		@Override
		public void valueChanged(ITable source, String key, Object value, boolean isNew) {
			if(running) {
				return;
			}
			
			running = true;
			SwingUtilities.invokeLater(new Runnable() {
				
				@Override
				public void run() {
					synchronized (table) {
						String state = table.getString("State", "Default State");
						String position = table.getString("Position", "Default Position");
						double currentDraw = table.getNumber("Current Draw", 0.0);
						double setpoint = table.getNumber("Setpoint", 0.0);
						double currentPosition = table.getNumber("Current Position", 0.0);
						double delta = table.getNumber("Delta", 0.0);
						boolean isDone = table.getBoolean("Is Done", false);
						
						grabberUIPanel.GetStatPanel().updateState(state, position, currentDraw, setpoint, currentPosition, delta, isDone);
						grabberUIPanel.GetGrabberPanel().update(currentPosition, setpoint);
						running = false;
					}
				}
			});
		}
	};
	
	@Override
	public void propertyChanged(Property property) {
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
		grabberUIPanel.GetStatPanel().updateState("Default State", "Default Position", 0.0, 0.0, 0.0, 0.0, false);
		grabberUIPanel.GetGrabberPanel().update(0.0, 0.0);
	}

}
