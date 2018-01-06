#include "../../pathfinder.h"
#include <math.h>


/*
 * This assumes that it's called with the correct time quantum, executing each step in order.
 */
double pathfinder_follow_distance(FollowerConfig c, DistanceFollower *follower, Segment *trajectory, int trajectory_length, double distance) {
    int segment = follower->segment;
    if (segment >= trajectory_length) {
        follower->finished = 1;
        follower->output = 0.0;
        Segment last = trajectory[trajectory_length - 1];
        follower->heading = last.heading;
        return 0.0;
    } else {
        double result = pathfinder_follow_distance_internal(c, follower, trajectory[segment + 1], distance);
        follower->segment = follower->segment + 1;
        return result;
    }
}

double pathfinder_follow_distance_internal(FollowerConfig c, DistanceFollower *follower, Segment s,
		double distance) {
	follower->finished = 0;
	double error = s.position - distance;
	double calculated_value = c.kp * error +
							  c.kd * ((error - follower->last_error) / s.dt) +
							  (c.kv * s.velocity + c.ka * s.acceleration);

	follower->last_error = error;
	follower->heading = s.heading;
	follower->output = calculated_value;

	return calculated_value;
}
