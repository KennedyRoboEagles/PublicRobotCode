/*
 * AutoRightCommandGroup.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include "Commands/Auto/AutoRightCommandGroup.h"
#include "Commands/Motion/DriveLinearForwardCommand.h"
#include "Commands/Auto/AutoInitCommandGroup.h"
#include "ConditionalTreeCommand.h"
#include "PlaceCubeOnSideCommandGroup.h"

#include <Commands/PrintCommand.h>

using namespace OpenRIO::PowerUp;
using namespace frc;

AutoRightCommandGroup::AutoRightCommandGroup() {
	// Wait for calibration
	AddParallel(new AutoInitCommandGroup());
	AddParallel(new PrintCommand("Starting Right Auto"));

	// Main Auto code
	AddParallel(
		new ConditionalTreeCommand(
			/*
			 * Check to see if the switch closest to use is owned on the right side
			 */
			new PlaceCubeOnSideCommandGroup(0, 0, 0, 0),
			MatchData::GameFeature::SWITCH_NEAR,
			MatchData::OwnedSide::RIGHT,
			new ConditionalTreeCommand(
					/*
					 * Check to see if the scale is owned on the right side
					 */
					new PlaceCubeOnSideCommandGroup(0, 0, 0, 0),
					MatchData::GameFeature::SCALE,
					MatchData::OwnedSide::RIGHT,
						/*
						 * Neither the scale or switch are on the RIght side
						 */
						new DriveLinearForwardCommand(0, 0)
			))
		);
}

AutoRightCommandGroup::~AutoRightCommandGroup() {
	// TODO Auto-generated destructor stub
}

