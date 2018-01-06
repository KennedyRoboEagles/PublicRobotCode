#ifndef PathFinderCommand_H
#define PathFinderCommand_H

#include "../../CommandBase.h"
#include "../../PathfinderCore/pathfinder.h"
#include <util/Logger.h>
#include "../../PathfinderCore/pathfinder/followers/TimeBasedDistancePathfinder.h"

#include <Notifier.h>
#include <atomic>


class PathFinderCommand : public CommandBase {
private:
	const char* separator = "----------------------------------------------------------------------------------------\n";
	int pointLength;
	Waypoint *points;
	Logger *logger;
	TimeBasedDistancePathfinder tbdPathfinder;

	double maxVelocity;
	double maxAcceleration;
	double maxJerk;

	double distanceX;
	double distanceY;
	double endHeading;

	int length;
	timespec lastTime;
	timespec startTime;
	Segment *trajectory;
	Segment *leftTrajectory;
	Segment *rightTrajectory;

	FollowerConfig leftConfig;
	DistanceFollower leftFollower;

	FollowerConfig rightConfig;
	DistanceFollower rightFollower;

	Notifier *updateNotifier;
	std::thread updateThread;

	std::atomic_bool finished;

	double kTurn;

	void cleanUp();
	void update();
	static void callUpdate(void* cmd);
	void DumpCandidate(TrajectoryCandidate candidate);
	void DumpSegments(const char* label, Segment* ideal, Segment* left, Segment* right, int length);
	void DumpWaypoints(Waypoint *points, int pointLength);
	void DumpPose(Pose *pose);
	void DumpDistanceFollower(const char *label, DistanceFollower* follower, Segment* segments, int segmentCount,
			double actualVelocity);
	void WriteSegmentsToCsv(Segment* trajectory, int segmentCount);
	static void WorkerThread(PathFinderCommand *commmand);
	void StartWorkerThread();
	void StopWorkerThread();

public:
	PathFinderCommand(double distanceX, double distanceY = 0, double endHeading = 0);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PathFinderCommand_H
