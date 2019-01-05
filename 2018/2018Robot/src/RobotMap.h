/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

/**
 * The RobotMap is a mapping from the ports sensors and actuators are wired into
 * to a variable name. This provides flexibility changing wiring, makes checking
 * the wiring easier and significantly reduces the number of magic numbers
 * floating around.
 */

// For example to map the left and right motors, you could define the
// following variables to use with your drivetrain subsystem.
// constexpr int kLeftMotor = 1;
// constexpr int kRightMotor = 2;

// If you are using multiple modules, make sure to define both the port
// number and the module. For example you with a rangefinder:
// constexpr int kRangeFinderPort = 1;
// constexpr int kRangeFinderModule = 1;

static constexpr int kCANIfierID = 0;

static constexpr int kChassisFrontLeftID         = 7;
static constexpr int kChassisRearLeftChannelID   = 3;
static constexpr int kChassisFrontRightChannelID = 8;
static constexpr int kChassisRearRightChannelID  = 4;

static constexpr int kElevatorMasterID = 1;
static constexpr int kElevatorSlaveID  = 2;
static constexpr int kElavatorBrakeChannel = 0;
static constexpr int kElevatorLow3rdStageLimitChannel  = 2;
static constexpr int kElevatorLow1stStageLimitChannel  = 4;
static constexpr int kElevatorHighLimitChannel         = 3;
static constexpr int kElevatorStartingConfigChannel    = 5;
static constexpr int kElevatorEncoderAChannel          = 0;
static constexpr int kElevatorEncoderBChannel          = 1;

static constexpr int kIntakeLeftId = 5;
static constexpr int kIntakeRightId = 6;
