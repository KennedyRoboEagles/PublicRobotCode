package com.kennedyrobotics;

import com.kennedyrobotics.commands.ShootLowGoalCommandGroup;
import com.kennedyrobotics.commands.DriveForwardFullBlastCommand;
import com.kennedyrobotics.commands.DriveTillLineCommand;
import com.kennedyrobotics.commands.EletroTestCommand;
import com.kennedyrobotics.commands.LowerCamera;
import com.kennedyrobotics.commands.PickupBallCommandGroup;
import com.kennedyrobotics.commands.PointAtTargetCommnad;
import com.kennedyrobotics.commands.RaiseCamera;
import com.kennedyrobotics.commands.TurnToTargetCommand;
import com.kennedyrobotics.commands.drive.TurnSpecifiedDegreesCommand;
import com.kennedyrobotics.commands.kicker.KickBallCommand;
import com.kennedyrobotics.commands.shooter.AimShooterToPositionCommand;
import com.kennedyrobotics.commands.test.TestAimShooterDownCommand;
import com.kennedyrobotics.commands.test.TestAimShooterUpCommand;
import com.kennedyrobotics.commands.test.TestExtendKickerCommand;
import com.kennedyrobotics.commands.test.TestRetractKickerCommand;
import com.kennedyrobotics.commands.test.TestShooterShootCommand;
import com.kennedyrobotics.commands.vision.VisionDriveToPosition;
import com.kennedyrobotics.commands.vision.VisionTargetCommandGroup;
import com.kennedyrobotics.commands.vision.VisionTurnToTarget;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.buttons.Button;
import edu.wpi.first.wpilibj.buttons.InternalButton;
import edu.wpi.first.wpilibj.buttons.JoystickButton;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
@SuppressWarnings("unused")
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
	
	private final Joystick driverStick = new Joystick(RobotMap.OI_JOYSTICK_DRIVER);
	private final Joystick shooterStick = new Joystick(RobotMap.OI_JOYSTICK_SHOOTER);
	private final Joystick testStick = new Joystick(RobotMap.OI_JOYSTICK_TEST);
	
	public OI() {
		JoystickButton driveForwardButton = new JoystickButton(driverStick, XboxPcJoystickMapping.LeftBumper);
		driveForwardButton.whileHeld(new DriveForwardFullBlastCommand());
		
		JoystickButton shooterShootLowGoalButton = new JoystickButton(shooterStick, RobotMap.OI_SHOOTER_SHOOT_LOW_GOAL);
		shooterShootLowGoalButton.whileHeld(new ShootLowGoalCommandGroup());
		
		JoystickButton shooterPickUpBall = new JoystickButton(shooterStick, RobotMap.OI_SHOOTER_PICKUP_BALL);
		shooterPickUpBall.whileHeld(new PickupBallCommandGroup());
		
		JoystickButton shooterShootHigh = new JoystickButton(shooterStick, XboxPcJoystickMapping.B);
		shooterShootHigh.whileHeld(new TestShooterShootCommand());
		
//		JoystickButton raiseCamera = new JoystickButton(driverStick, 3);
//		raiseCamera.whenPressed(new RaiseCamera());
//		
//		JoystickButton lowerCamera = new JoystickButton(driverStick, 2);
//		lowerCamera.whenPressed(new LowerCamera());
//		
//		JoystickButton testRetractArmButton = new JoystickButton(testStick, 2);
//		testRetractArmButton.whileHeld(new TestRetractArmCommand());
//		
		JoystickButton testExtendKickerButton = new JoystickButton(testStick, 1);
		testExtendKickerButton.whileHeld(new TestExtendKickerCommand());
		JoystickButton testRetractKickerButton = new JoystickButton(testStick, 5);
		testRetractKickerButton.whileHeld(new TestRetractKickerCommand());
		
//		
//		JoystickButton testExtendArmButton = new JoystickButton(testStick, 3);
//		testExtendArmButton.whileHeld(new TestExtendArmCommand());
//		
//		
//		JoystickButton testRaiseArmButton = new JoystickButton(testStick, 6);
//		testRaiseArmButton.whileHeld(new TestRaiseArmCommand());
//		
//		JoystickButton testLowerArmButton = new JoystickButton(testStick, 7);
//		testLowerArmButton.whileHeld(new TestLowerArmCommand());
//		
		JoystickButton testAimShooterDownButton = new JoystickButton(testStick, 10);
		testAimShooterDownButton.whileHeld(new TestAimShooterDownCommand());
		
		JoystickButton testAimShooterUpButton = new JoystickButton(testStick, 11);
		testAimShooterUpButton.whileHeld(new TestAimShooterUpCommand());

		JoystickButton testShooterButton = new JoystickButton(testStick, 8);
		testShooterButton.whileHeld(new TestShooterShootCommand() );
		
		JoystickButton testEectroB = new JoystickButton(testStick, XboxPcJoystickMapping.LeftBumper);
		testEectroB.whileHeld(new EletroTestCommand());
		
		if(Robot.DEBUG_SD_BUTTONS) {
			SmartDashboard.putData("Kick Ball Cmd", new KickBallCommand());
			
			SmartDashboard.putData("Turn 90", new TurnSpecifiedDegreesCommand(90));
			SmartDashboard.putData("Turn -90", new TurnSpecifiedDegreesCommand(-90));
			
			SmartDashboard.putData("Test Line", new DriveTillLineCommand(-0.7));
			SmartDashboard.putData("Vision 10ft", new VisionDriveToPosition(10));
			SmartDashboard.putData("Vision Turn", new VisionTurnToTarget());
			SmartDashboard.putData("Vision Target", new VisionTargetCommandGroup());
		}
	}
	
	public Joystick getDriverStick() {
		return driverStick;
	}
	
	public Joystick getShooterStick() {
		return shooterStick;
	}
	
}