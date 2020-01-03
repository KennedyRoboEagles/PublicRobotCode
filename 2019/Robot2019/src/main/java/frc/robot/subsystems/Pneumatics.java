/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package frc.robot.subsystems;

import edu.wpi.first.wpilibj.AnalogInput;
import edu.wpi.first.wpilibj.Compressor;
import edu.wpi.first.wpilibj.RobotController;
import edu.wpi.first.wpilibj.command.Subsystem;
import edu.wpi.first.wpilibj.smartdashboard.SmartDashboard;
import frc.robot.RobotMap;

/**
 * Add your docs here.
 */
public class Pneumatics extends Subsystem {
  // Put methods for controlling this subsystem
  // here. Call these from Commands.

  private static final Pneumatics instance_ = new Pneumatics();
  public static final Pneumatics getInstance() {
    return instance_;
  }

  private final Compressor compressor_ = new Compressor();
  private final AnalogInput pressureTransducer = new AnalogInput(RobotMap.kPressureTransducerChannel);


  @Override
  public void initDefaultCommand() {
    // Set the default command for a subsystem here.
    // setDefaultCommand(new MySpecialCommand());
  }

  public void init() {
    compressor_.start();
  }

  @Override
  public void periodic() {
    SmartDashboard.putNumber("Compressor current", compressor_.getCompressorCurrent());
    SmartDashboard.putBoolean("Pressure switch", compressor_.getPressureSwitchValue());
    SmartDashboard.putNumber("Tank pressure", this.tankPressure());

    SmartDashboard.putBoolean("Over 45", this.tankPressure() > 45);
    SmartDashboard.putBoolean("Over 50", this.tankPressure() > 50);

  }

  /**
   * Get the pressure in PSI
   */
  public double tankPressure() {
    double vcc = RobotController.getVoltage5V();
    double vout = pressureTransducer.getAverageVoltage();

    return 250 * (vout / vcc) - 25;
  }
}
