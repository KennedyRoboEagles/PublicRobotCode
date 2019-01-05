/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "TestCondCommandGroup.h"


#include <Commands/PrintCommand.h>
#include "Commands/Auto/ConditionalTreeCommand.h"

using namespace OpenRIO::PowerUp;
using namespace frc;

TestCondCommandGroup::TestCondCommandGroup() {
	AddParallel(new PrintCommand("Starting Left Auto"));

//	// Main Auto code
//	AddParallel(
//		new ConditionalTreeCommand(
//			/*
//			 * Check to see if the switch closest to use is owned on the left side
//			 */
//			new PrintCommand("SWITCH IS OWNED - LEFT"),
//			MatchData::GameFeature::SWITCH_NEAR,
//			MatchData::OwnedSide::LEFT,
//			new ConditionalTreeCommand(
//					/*
//					 * Check to see if the switch closest to use is owned on the right side
//					 */
//					new PrintCommand("SCALE IS OWNED- RIGHT"),
//					MatchData::GameFeature::SWITCH_NEAR,
//					MatchData::OwnedSide::RIGHT,
//						/*
//						 * Error Condition, should be one or the other, just drive forward
//						 */
//						new PrintCommand("Error")
//
//			))
//		);
	// Main Auto code
	AddParallel(
		new ConditionalTreeCommand(
			/*
			 * Check to see if the switch closest to use is owned on the left side
			 */
			new PrintCommand("SWITCH IS OWNED - LEFT"),
			MatchData::GameFeature::SWITCH_NEAR,
			MatchData::OwnedSide::RIGHT,
			new ConditionalTreeCommand(
					/*
					 * Check to see if the switch closest to use is owned on the right side
					 */
					new PrintCommand("SCALE IS OWNED - LEFT"),
					MatchData::GameFeature::SCALE,
					MatchData::OwnedSide::RIGHT,
						/*
						 * Error Condition, should be one or the other, just drive forward
						 */
						new PrintCommand("Neither is owned")

			))
		);


}
