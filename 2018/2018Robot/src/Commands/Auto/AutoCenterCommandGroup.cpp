/*
 * AutoCenterCommandGroup.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include "Commands/Auto/AutoCenterCommandGroup.h"
#include "Commands/Motion/DriveLinearForwardCommand.h"
#include "ConditionalTreeCommand.h"
#include "Commands/Auto/PlaceCubeOnSwitchCenterCommandGroup.h"
#include "Commands/Auto/AutoInitCommandGroup.h"

#include <Commands/PrintCommand.h>

using namespace OpenRIO::PowerUp;
using namespace frc;

AutoCenterCommandGroup::AutoCenterCommandGroup() {
	// Wait for calibration
	AddParallel(new AutoInitCommandGroup());
	AddParallel(new PrintCommand("Starting Left Auto"));

	// Main Auto code
	AddParallel(
		new ConditionalTreeCommand(
			/*
			 * Check to see if the switch closest to use is owned on the left side
			 */
			new PlaceCubeOnSwitchCenterCommandGroup(0, 0, 0, 0),
			MatchData::GameFeature::SWITCH_NEAR,
			MatchData::OwnedSide::LEFT,
			new ConditionalTreeCommand(
					/*
					 * Check to see if the switch closest to use is owned on the right side
					 */
					new PlaceCubeOnSwitchCenterCommandGroup(0, 0, 0, 0),
					MatchData::GameFeature::SWITCH_NEAR,
					MatchData::OwnedSide::RIGHT,
						/*
						 * Error Condition, should be one or the other, just drive forward
						 */
						new DriveLinearForwardCommand(0, 0)
			))
		);
}

AutoCenterCommandGroup::~AutoCenterCommandGroup() {}

