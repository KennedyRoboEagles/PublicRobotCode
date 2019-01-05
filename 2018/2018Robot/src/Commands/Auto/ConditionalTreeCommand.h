/*
 * ConditionalTreeCommand.h
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#ifndef SRC_COMMANDS_AUTO_CONDITIONALTREECOMMAND_H_
#define SRC_COMMANDS_AUTO_CONDITIONALTREECOMMAND_H_

#include <Commands/ConditionalCommand.h>
#include "Util/MatchData.h"


class ConditionalTreeCommand: public frc::ConditionalCommand {
public:
	ConditionalTreeCommand(frc::Command* onTrue, OpenRIO::PowerUp::MatchData::GameFeature feature, OpenRIO::PowerUp::MatchData::OwnedSide side, frc::Command* onFalse);
	virtual ~ConditionalTreeCommand();
	bool Condition() override;
private:
	OpenRIO::PowerUp::MatchData::GameFeature feature_;
	OpenRIO::PowerUp::MatchData::OwnedSide side_;
};

#endif /* SRC_COMMANDS_AUTO_CONDITIONALTREECOMMAND_H_ */
