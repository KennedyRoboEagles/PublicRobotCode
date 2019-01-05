/*
 * ConditionalTreeCommand.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include <Commands/Auto/ConditionalTreeCommand.h>

using namespace OpenRIO::PowerUp;

ConditionalTreeCommand::ConditionalTreeCommand(frc::Command* onTrue, MatchData::GameFeature feature, MatchData::OwnedSide side, frc::Command* onFalse)
	: ConditionalCommand(onTrue, onFalse){

	side_ = side;
	feature_ = feature;

}

ConditionalTreeCommand::~ConditionalTreeCommand() {}

bool ConditionalTreeCommand::Condition() {
	return MatchData::get_owned_side(feature_) == side_;
}
