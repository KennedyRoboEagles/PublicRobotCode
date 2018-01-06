#ifndef PathFinderCommand2_H
#define PathFinderCommand2_H

#include "../../CommandBase.h"
#include "../../PathfinderCore/pathfinder.h"
#include <util/Logger.h>
#include "../../PathfinderCore/pathfinder/followers/TimeBasedDistancePathfinder.h"

#include <Notifier.h>
#include <atomic>


class ArcTurnCommand : public CommandBase {
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

	bool leftDrive;

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
	static void WorkerThread(ArcTurnCommand *commmand);
	void StartWorkerThread();
	void StopWorkerThread();

public:
	ArcTurnCommand(double angle, bool left);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
};

#endif  // PathFinderCommand2_H
