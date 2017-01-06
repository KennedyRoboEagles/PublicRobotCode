package com.kennedyrobotics.robot2016;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.JoystickButton;

import static com.kennedyrobotics.robot2016.RobotMap.*;

import com.kennedyrobotics.robot2016.commands.ExtendArmCommand;
import com.kennedyrobotics.robot2016.commands.LowerArmCommand;
import com.kennedyrobotics.robot2016.commands.LowerShooterCommand;
import com.kennedyrobotics.robot2016.commands.RaiseArmCommand;
import com.kennedyrobotics.robot2016.commands.RaiseShooterCommand;
import com.kennedyrobotics.robot2016.commands.RetractArmCommand;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {
    //// CREATING BUTTONS
    // One type of button is a joystick button which is any button on a joystick.
    // You create one by telling it which joystick it's on and which button
    // number it is.
    // Joystick stick = new Joystick(port);
    // Button button = new JoystickButton(stick, buttonNumber);
    
    // There are a few additional built in buttons you can use. Additionally,
    // by subclassing Button you can create custom triggers and bind those to
    // commands the same as any other Button.
    
    //// TRIGGERING COMMANDS WITH BUTTONS
    // Once you have a button, it's trivial to bind it to a button in one of
    // three ways:
    
    // Start the command when the button is pressed and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenPressed(new ExampleCommand());
    
    // Run the command while the button is being held down and interrupt it once
    // the button is released.
    // button.whileHeld(new ExampleCommand());
    
    // Start the command when the button is released  and let it run the command
    // until it is finished as determined by it's isFinished method.
    // button.whenReleased(new ExampleCommand());
	
	private final Joystick driverStick = new Joystick(OI_JOYSTICK_DRIVER);
	public Joystick getDriverStick() {
		return driverStick;
	}
	
	public OI() {
		JoystickButton raiseArm = new JoystickButton(driverStick, OI_DRIVER_RAISE_ARM);
		raiseArm.whileHeld(new RaiseArmCommand());
		JoystickButton lowerArm = new JoystickButton(driverStick, OI_DRIVER_LOWER_ARM);
		lowerArm.whileHeld(new LowerArmCommand());
		JoystickButton extendArm = new JoystickButton(driverStick, OI_DRIVER_EXTEND_ARM);
		extendArm.whileHeld(new ExtendArmCommand());
		JoystickButton retractArm = new JoystickButton(driverStick, OI_DRIVER_RETRACT_ARM);
		retractArm.whileHeld(new RetractArmCommand());
		JoystickButton raiseShooter = new JoystickButton(driverStick, OI_DRIVER_RAISE_SHOOTER);
		raiseShooter.whileHeld(new RaiseShooterCommand());
		JoystickButton lowerShooter = new JoystickButton(driverStick, OI_DRIVER_LOWER_SHOOTER);
		lowerShooter.whileHeld(new LowerShooterCommand());
	}
	
}

