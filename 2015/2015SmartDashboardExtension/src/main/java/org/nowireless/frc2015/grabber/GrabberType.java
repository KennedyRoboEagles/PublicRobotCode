package org.nowireless.frc2015.grabber;

import edu.wpi.first.smartdashboard.types.NamedDataType;

public class GrabberType extends NamedDataType {
	public static final String LABEL = "Grabber";
	
	private GrabberType() {
		super(LABEL, Grabber.class);
	}
	
	public static NamedDataType get() {
		if (NamedDataType.get(LABEL) != null) {
			return NamedDataType.get(LABEL);
		} else {
			return new GrabberType();
		}
	}
}
