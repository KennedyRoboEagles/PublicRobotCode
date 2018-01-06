/*
 * TimeBasedDistancePathfinder.h
 *
 *  Created on: Feb 10, 2017
 *      Author: steve
 */

#ifndef SRC_PATHFINDERCORE_PATHFINDER_FOLLOWERS_TIMEBASEDDISTANCEPATHFINDER_H_
#define SRC_PATHFINDERCORE_PATHFINDER_FOLLOWERS_TIMEBASEDDISTANCEPATHFINDER_H_

#include "../../pathfinder.h"
#include "../../../Util/Logger.h"

class TimeBasedDistancePathfinder {
public:
	double Follow(FollowerConfig c, DistanceFollower *follower, Segment *trajectory,
			int trajectory_length, double distance, long elapsedTimeinMicroSeconds, double dt, Logger* logger);
};

#endif /* SRC_PATHFINDERCORE_PATHFINDER_FOLLOWERS_TIMEBASEDDISTANCEPATHFINDER_H_ */
