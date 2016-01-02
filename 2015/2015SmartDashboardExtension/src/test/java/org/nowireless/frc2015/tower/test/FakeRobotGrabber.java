package org.nowireless.frc2015.tower.test;

import edu.wpi.first.wpilibj.NamedSendable;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj.tables.ITable;

public class FakeRobotGrabber {

	public static class GrabberSendable implements NamedSendable {
		ITable table;

		@Override
		public void initTable(ITable subtable) {
			// TODO Auto-generated method stub
			this.table = subtable;
		}

		@Override
		public ITable getTable() {
			// TODO Auto-generated method stub
			return table;
		}

		@Override
		public String getSmartDashboardType() {
			// TODO Auto-generated method stub
			return "Grabber";
		}

		@Override
		public String getName() {
			// TODO Auto-generated method stub
			return "Grabber";
		}
		
		public void test() {
			table.putString("State", "Default State");
			table.putString("Position", "Default Position");
			table.putNumber("Current Draw", 0.0);
			table.putNumber("Setpoint", 0.0);
			table.putNumber("Current Position", 0.0);
			table.putNumber("Delta", 0.0);
			table.putBoolean("Is Done", false);
		}
	}
	
	public static void main(String[] args) {
		NetworkTable.setClientMode();
		NetworkTable.setIPAddress("127.0.0.1");
		
		GrabberSendable grabberSendable = new GrabberSendable();
		SmartDashboard.putData(grabberSendable);
		grabberSendable.test();
	}

}
