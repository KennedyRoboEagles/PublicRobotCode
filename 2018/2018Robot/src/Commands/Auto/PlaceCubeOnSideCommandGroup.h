/*
 * PlaceCubeOnSideCommandGroup.h
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#ifndef SRC_COMMANDS_AUTO_PLACECUBEONSIDECOMMANDGROUP_H_
#define SRC_COMMANDS_AUTO_PLACECUBEONSIDECOMMANDGROUP_H_

#include <Commands/CommandGroup.h>

class PlaceCubeOnSideCommandGroup: public frc::CommandGroup {
public:
	PlaceCubeOnSideCommandGroup(double firstDistance, double secondHeading, double thridDistance, double evevatorHeight);
	virtual ~PlaceCubeOnSideCommandGroup();
};

#endif /* SRC_COMMANDS_AUTO_PLACECUBEONSIDECOMMANDGROUP_H_ */
