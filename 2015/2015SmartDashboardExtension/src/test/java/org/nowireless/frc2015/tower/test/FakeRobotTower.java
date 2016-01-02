package org.nowireless.frc2015.tower.test;

import edu.wpi.first.wpilibj.NamedSendable;
import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import edu.wpi.first.wpilibj.tables.ITable;

public class FakeRobotTower {

	public static class TowerSendable implements NamedSendable {

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
			return "Tower";
		}

		@Override
		public String getName() {
			// TODO Auto-generated method stub
			return "Tower";
		}
		
		public void test() {
			table.putString("Position", "Unknown Position");
			table.putString("State", "Unknown State");
			table.putNumber("Force Voltage", 0.0);
			table.putBoolean("At Position", false);
			table.putNumber("Setpoint", 0.0);
			table.putNumber("Current Position", 0.0);
			table.putNumber("Delta", 0.0);
			table.putBoolean("Upper Limit", false);
			table.putBoolean("Lower Limit", false);
		
		}
		
	}
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		NetworkTable.setClientMode();
		NetworkTable.setIPAddress("127.0.0.1");
		
		SmartDashboard.putBoolean("Hellow", true);
		TowerSendable tower = new TowerSendable();
		SmartDashboard.putData(tower);
		tower.test();
		
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		int i = 0;
		while (true) {
			tower.table.putNumber("Current Position", i);
			i++;
			try {
				Thread.sleep(500);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
	}

}
