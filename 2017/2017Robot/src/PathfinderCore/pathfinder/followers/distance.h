#ifndef PATHFINDER_FOL_DISTANCE_H_DEF
#define PATHFINDER_FOL_DISTANCE_H_DEF

#include "../lib.h"

CAPI typedef struct {
    double kp, ki, kd, kv, ka;
} FollowerConfig;

CAPI typedef struct {
    double last_error, heading, output;
    int segment, finished;
} DistanceFollower;

CAPI double pathfinder_follow_distance(FollowerConfig c, DistanceFollower *follower, Segment *trajectory, int trajectory_length, double distance);

CAPI double pathfinder_follow_distance_internal(FollowerConfig c, DistanceFollower *follower, Segment s, double distance);
#endif
