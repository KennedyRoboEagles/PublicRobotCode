/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot;

import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.XboxController;
import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.buttons.JoystickButton;
import frc.robot.commands.LowerAndCaputureCargo;
import frc.robot.commands.cargo.CaptureCargoCommand;
import frc.robot.commands.cargo.ThrowCargoCommand;
import frc.robot.commands.hatch.CaptureHatchCommand;
import frc.robot.commands.hatch.KickHatchOffCommand;
import frc.robot.commands.hatch.ReleaseHatchCommand;
import frc.robot.commands.intake.ControlIntakePivotCommand;
import frc.robot.commands.lift.ControlLiftCommand;
import frc.robot.commands.lift.LiftRobotCommand;
import frc.robot.commands.lift.LiftRobotLVL2Command;
import frc.robot.subsystems.Lift;
import frc.robot.triggers.DPadTrigger;
import frc.robot.triggers.DPadTrigger.DPad;

/**
 * This class is the glue that binds the controls on the physical operator
 * interface to the commands and command groups that allow control of the robot.
 */
public class OI {

  private static final OI instance_ = new OI();
  public static OI getInstance() { return instance_; }

  //// CREATING BUTTONS
  // One type of button is a joystick button which is any button on a
  //// joystick.
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

  // Start the command when the button is released and let it run the command
  // until it is finished as determined by it's isFinished method.
  // button.whenReleased(new ExampleCommand());

  public final XboxController driver = new XboxController(0);
  public final XboxController secoond  = new XboxController(1);
  // public final XboxController intakeController = new XboxController(1);

  // public final Joystick tester = new  Joystick(2);

  public OI() {
    // JoystickButton driveLiftButton = new JoystickButton(driver, 1);
    // driveLiftButton.whileHeld(new ControlDriveLiftMotorCommand());

    // JoystickButton captureCargo = new JoystickButton(intakeController, 1);
    // captureCargo.whenPressed(new CaptureCargoCommand());

    JoystickButton throwCargo = new JoystickButton(driver, 2);
    throwCargo.whenPressed(new ThrowCargoCommand()); 

    DPadTrigger pivotUp = new DPadTrigger(driver, DPad.kUp);
    pivotUp.whileActive(new ControlIntakePivotCommand(ControlIntakePivotCommand.Direction.kUp));

    DPadTrigger pivotDown = new DPadTrigger(driver, DPad.KDown);
    // pivotDown.whileActive(new ControlIntakePivotCommand(ControlIntakePivotCommand.Direction.kDown));
    pivotDown.whenActive(new LowerAndCaputureCargo());

    // JoystickButton kickHatch = new JoystickButton(driver, 6);
    // kickHatch.whenPressed(new KickHatchOffCommand());

    JoystickButton captureHatch = new JoystickButton(driver, 5);
    captureHatch.whenPressed(new CaptureHatchCommand());

    JoystickButton releaseHatch = new JoystickButton(driver, 6);
    releaseHatch.whenPressed(new ReleaseHatchCommand());


    JoystickButton lift  = new JoystickButton(secoond, 3);
    lift.whenPressed(new LiftRobotCommand());

    JoystickButton liftLvl2 = new JoystickButton(secoond, 1);
    lift.whenPressed(new LiftRobotLVL2Command());

    JoystickButton raiseFront = new JoystickButton(secoond, 4);
    raiseFront.whenPressed(new ControlLiftCommand(Lift.getFrontInstance(), ControlLiftCommand.Value.kRetract));

    JoystickButton raiseBack = new JoystickButton(secoond, 2);
    raiseBack.whenPressed(new ControlLiftCommand(Lift.getBackInstance(), ControlLiftCommand.Value.kRetract));
  }

  public double throttle() {
    double left = driver.getTriggerAxis(Hand.kLeft);
    double right = driver.getTriggerAxis(Hand.kRight);
  
    if(left < right) {
      return right;
    } else {
      return -left;
    }
  }

  public double rotate() {
    return driver.getX(Hand.kLeft);
  }

  public boolean isQuickTurn() {
    return driver.getAButton();
  }

  public double secondThrottle() {
    double left = secoond.getTriggerAxis(Hand.kLeft);
    double right = secoond.getTriggerAxis(Hand.kRight);
  
    if(left < right) {
      return right;
    } else {
      return -left;
    }
  }


}