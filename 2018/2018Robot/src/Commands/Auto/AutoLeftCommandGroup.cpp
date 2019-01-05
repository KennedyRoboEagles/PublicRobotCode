/*
 * AutoLeftCommandGroup.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include "Commands/Auto/AutoLeftCommandGroup.h"
#include "Commands/Motion/DriveLinearForwardCommand.h"
#include "Commands/Auto/AutoInitCommandGroup.h"
#include "ConditionalTreeCommand.h"
#include "PlaceCubeOnSideCommandGroup.h"

#include <Commands/PrintCommand.h>

using namespace OpenRIO::PowerUp;
using namespace frc;

AutoLeftCommandGroup::AutoLeftCommandGroup() {
	// Wait for calibration
	AddParallel(new AutoInitCommandGroup());
	AddParallel(new PrintCommand("Starting Left Auto"));

	// Main Auto code
	AddParallel(
		new ConditionalTreeCommand(
			/*
			 * Check to see if the switch closest to use is owned on the left side
			 */
			new PlaceCubeOnSideCommandGroup(0, 0, 0, 0),
			MatchData::GameFeature::SWITCH_NEAR,
			MatchData::OwnedSide::LEFT,
			new ConditionalTreeCommand(
					/*
					 * Check to see if the scale is owned on the left side
					 */
					new PlaceCubeOnSideCommandGroup(0, 0, 0, 0),
					MatchData::GameFeature::SCALE,
					MatchData::OwnedSide::LEFT,
						/*
						 * Neither the scale or switch are on the left side
						 */
						new DriveLinearForwardCommand(0, 0)
			))
		);
}

AutoLeftCommandGroup::~AutoLeftCommandGroup() {}

