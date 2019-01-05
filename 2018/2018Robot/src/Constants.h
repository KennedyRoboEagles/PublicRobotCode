/*
 * Constants.h
 *
 *  Created on: Feb 18, 2018
 *      Author: nowir
 */

#ifndef SRC_CONSTANTS_H_
#define SRC_CONSTANTS_H_

/**
 * Setting any of these to false will disable creation of
 * that subsystem.
 */
constexpr bool kEnableSubsystemChassis  = true;
constexpr bool kEnableSubsystemSensors  = true;
constexpr bool kEnableSubsystemElevator = true;
constexpr bool kEnableSubsystemIntake   = true;

constexpr bool kUseXboxController = true;

#endif /* SRC_CONSTANTS_H_ */
