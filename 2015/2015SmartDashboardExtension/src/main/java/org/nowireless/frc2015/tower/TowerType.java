package org.nowireless.frc2015.tower;

import edu.wpi.first.smartdashboard.types.NamedDataType;

public class TowerType extends NamedDataType {
	public static final String LABEL = "Tower";
	
	private TowerType() {
		super(LABEL, Tower.class);
	}
	
	public static NamedDataType get() {
        if (NamedDataType.get(LABEL) != null) {
            return NamedDataType.get(LABEL);
        } else {
            return new TowerType();
        }
    }
}
