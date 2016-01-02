package org.nowireless.frc2015.tower;

import java.util.HashMap;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Set;

public class TowerPosition {
	
	private static Map<String, Double> positions = null;
	private static Set<Entry<String, Double>> entrys = null;
	
	public static Set<Entry<String, Double>> GetPositions() {
		if(positions == null) {
			positions = new HashMap<String, Double>();
			positions.put("Button", 9.5);
			positions.put("Stack Up", 26.0);
			positions.put("Picked Up Bin", 30.0);
			positions.put("Second Tote Acquisition", 21.5);
			positions.put("Clear Player Station", 47.0);
			positions.put("Bin Clear 4 Stack", 55.25);
			
			entrys = positions.entrySet();
		}
		
		return entrys;
	}
}
