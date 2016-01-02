package org.nowireless.frc2015.tower.test;

import java.lang.reflect.Field;
import java.lang.reflect.Modifier;

import org.nowireless.frc2015.tower.Tower;

import edu.wpi.first.smartdashboard.gui.Widget;
import edu.wpi.first.smartdashboard.types.DataType;

public class UITest2 {
	public static void main(String[] args) {
		Class<? extends Widget> clazz = Tower.class;
		
		if(Modifier.isAbstract(clazz.getModifiers())) {
			System.out.println("Class is abstract");
		}
		
		try {
			Field field = clazz.getDeclaredField("TYPES");
			int modifiers = field.getModifiers();
			if (!Modifier.isStatic(modifiers)) {
				throw new RuntimeException("TYPES must be static");
			} else if (!Modifier.isFinal(modifiers)) {
				throw new RuntimeException("TYPES must be final");
			}
			
			DataType[] types = (DataType[]) field.get(null);
			System.out.println(types.length);
		} catch (NoSuchFieldException | SecurityException | IllegalArgumentException | IllegalAccessException e) {
			e.printStackTrace();
		}
	}
}
