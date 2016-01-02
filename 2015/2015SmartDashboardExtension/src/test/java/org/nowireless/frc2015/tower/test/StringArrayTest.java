package org.nowireless.frc2015.tower.test;

import edu.wpi.first.wpilibj.networktables.NetworkTable;
import edu.wpi.first.wpilibj.networktables2.type.StringArray;

public class StringArrayTest {

	public static void main(String[] args) {
		NetworkTable.setClientMode();
		NetworkTable.setIPAddress("localhost");
		StringArray array = new StringArray();
		array.add("Zero");
		array.add("One");
		array.add("Two");
		
		NetworkTable.getTable("Test").putValue("Strings1", array);
		
		System.out.println(NetworkTable.getTable("Test").getValue("Strings1").getClass().getSimpleName());
		
		/*for(int i = 0; i < theArray.size(); i++) {
			System.out.println(theArray.get(i));
		}*/
	}

}
