/*
 * TimeBasedDistancePathfinder.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: steve
 */

#include <PathfinderCore/pathfinder/followers/TimeBasedDistancePathfinder.h>

/*
 * This follower uses the current elapsed time of the run to select which segment to execute.
 */
double TimeBasedDistancePathfinder::Follow(FollowerConfig c, DistanceFollower *follower, Segment *trajectory,
	int trajectory_length, double distance, long elapsedTimeInMicroseconds, double dt, Logger* logger)
{
    int lastSegment = follower->segment;
	int segmentToRun = (int) rint(elapsedTimeInMicroseconds / (dt * (double) 1000000));

    if (segmentToRun >= trajectory_length || lastSegment >= trajectory_length) {
    	// We are done.  Clean up.

		follower->segment = trajectory_length;
        follower->finished = 1;
        follower->output = 0.0;
        Segment last = trajectory[trajectory_length - 1];
        follower->heading = last.heading;

        return 0.0;
    } else {
    	if (NULL != logger && segmentToRun > lastSegment + 1)
    	{
    		logger->Log("TimeBasedDistancePathfinder: skipping segments -- current: %d, last: %d\n",
    				segmentToRun, lastSegment);
    	}

        double result = pathfinder_follow_distance_internal(c, follower, trajectory[segmentToRun], distance);
        follower->segment = segmentToRun;

        return result;
    }
}
