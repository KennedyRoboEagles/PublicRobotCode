#include "ArcTurnCommand.h"
#include "../../PathfinderCore/pathfinder.h"
#include "../../Util/MathUtil.h"
#include "../../RobotConstants.h"
#include <util/Logger.h>
#include <Preferences.h>
#include <util/TimeUtil.h>
#include <pthread.h>

constexpr double kDT = 1/150.0;

// DEBUG_PATHFINDER controls whether we dump path calcuations to console.
//#define DEBUG_PATHFINDER

// CALCULATE_ONLY, if true, only performs calculations, but does not execute the path.
// #define CALCULATE_ONLY	1

#define	DEBUG_WORKER_THREAD

//#define IMU_HEADING_CORRECTION

ArcTurnCommand::ArcTurnCommand(double angle, bool leftDrive) {
	// Use Requires() here to declare subsystem dependencies
	// eg. Requires(Robot::chassis.get());
	Requires(chassis.get());

	this->leftDrive = leftDrive;

	logger = new Logger("/home/lvuser/pathfinder.log");
	tbdPathfinder = TimeBasedDistancePathfinder();

	pointLength = 0;
	points = nullptr;
	length = 0;
	trajectory = nullptr;
	leftTrajectory = nullptr;
	rightTrajectory = nullptr;

	double arc = d2r(angle) * kWHEELBASE_WIDTH;

	this->distanceX = arc;
	this->distanceY = 0;
	this->endHeading = 0;

	updateNotifier = new Notifier(ArcTurnCommand::callUpdate, this);

	double kp = 0;
	double ki = 0;
	double kd = 0;
	double kv = 0;
	double ka = 0;
	kTurn = 0;

	leftConfig.kp = kp;
	leftConfig.ki= ki;
	leftConfig.kd = kd;
	leftConfig.kv = kv;
	leftConfig.ka = ka;

	rightConfig.kp = kp;
	rightConfig.ki= ki;
	rightConfig.kd = kd;
	rightConfig.kv = kv;
	rightConfig.ka = ka;
	
	maxVelocity = maxAcceleration = maxJerk = 0;

	lastTime.tv_nsec = 0;
	lastTime.tv_sec = 0;
}

void ArcTurnCommand::callUpdate(void* cmd) {
	printf("Updating\n");
	((ArcTurnCommand*)cmd)->update();
}

// Called just before this Command runs the first time
void ArcTurnCommand::Initialize() {
	Preferences* prefs = Preferences::GetInstance();
	double kp = prefs->GetDouble("kp", 0.5);
	double ki = prefs->GetDouble("ki", 0.0);
	double kd = prefs->GetDouble("kd", 0.0);

	//kv is about 1/(10f/s)=0.1
	//Since we are limited by our slower wheel, our true max velocity may be
	//about 75% * 10f/s=7.5f/s. So 1/7.5 = 0.133
	//So it looks like our experimentally found kv value of 0.115ish is right
	//between the 2, which is good.
	//A Note: as we move forward we are going to try to use the characteristic
	//plot/trendline of each wheel to correct for mechanical differences.
	//Which may effect kv a bit, but it should be beneficial.
	double kv_left  = prefs->GetDouble("kv_left", 0.115);
	double kv_right = prefs->GetDouble("kv_right", 0.11);
	double ka_left  = prefs->GetDouble("ka_left", 0.045);
	double ka_right = prefs->GetDouble("ka_right", 0.045);

	this->maxVelocity = prefs->GetDouble("arcMaxVelocity", DEFAULT_MAX_ALLOWED_VELOCITY);
	this->maxAcceleration = prefs->GetDouble("arcMaxAcceleration", DEFAULT_MAX_ALLOWED_ACCELERATION);
	this->maxJerk = prefs->GetDouble("arcMaxJerk", DEFAULT_MAX_ALLOWED_JERK);

	kTurn = Preferences::GetInstance()->GetDouble("kturn",0);

	leftConfig.kp = kp;
	leftConfig.ki = ki;
	leftConfig.kd = kd;
	leftConfig.kv = kv_left;
	leftConfig.ka = ka_left;

	rightConfig.kp = kp;
	rightConfig.ki = ki;
	rightConfig.kd = kd;
	rightConfig.kv = kv_right;
	rightConfig.ka = ka_right;

#ifdef DEBUG_PATHFINDER
	logger->Log(separator);
	logger->Log("Pathfinder configuration:\n");
	logger->Log("  Left: kp: %lf, ki: %lf, kd: %lf, kv: %lf, ka: %lf\n",
			leftConfig.kp, leftConfig.ki, leftConfig.kd, leftConfig.kv_right, leftConfig.ka_right);
	logger->Log("  Right: kp: %lf, ki: %lf, kd: %lf, kv: %lf, ka: %lf\n",
			rightConfig.kp, rightConfig.ki, rightConfig.kd, rightConfig.kv_right, rightConfig.ka_right);
	logger->Log("\n");
#endif

	SmartDashboard::PutBoolean("Path ready", false);
	printf("Pathfinder command starting\n");

	pointLength = 2;
	points = new Waypoint[pointLength];
	Waypoint p1 = {0, 0, 0};
//	Waypoint p2 = {12, 0, 0};
	Waypoint p2 = {distanceX, distanceY, endHeading};
//	Waypoint p2 = {3, 0, 0};
	points[0] = p1;
	points[1] = p2;

	TrajectoryCandidate candidate;
#ifdef DEBUG_PATHFINDER
	DumpWaypoints(points, pointLength);
#endif

	printf("Preparing path\n");
	pathfinder_prepare(points, pointLength, FIT_HERMITE_CUBIC, PATHFINDER_SAMPLES_FAST, kDT,
			this->maxVelocity, this->maxAcceleration, this->maxJerk, &candidate);
	printf("Path calculation completed.\n");

#ifdef	DEBUG_PATHFINDER
	DumpCandidate(candidate);
#endif

	length = candidate.length;
	trajectory = new Segment[length];
	// TODO need to check return value above for < 0, as it indicates an error.

	printf("Generating path\n");
	pathfinder_generate(&candidate, trajectory);
#ifdef	DEBUG_PATHFINDER
	WriteSegmentsToCsv(trajectory, length);
#endif

	leftTrajectory = new Segment[length];
	rightTrajectory = new Segment[length];

	double wheelBaseWidth = kWHEELBASE_WIDTH;

	printf("Modifying path\n");
	pathfinder_modify_tank(trajectory, length, leftTrajectory, rightTrajectory, wheelBaseWidth);
#ifdef	DEBUG_PATHFINDER_SEGMENT_DETAIL
	DumpSegments("Tank", trajectory, leftTrajectory, rightTrajectory, length);
#endif

	leftFollower.segment = 0;
	leftFollower.last_error = 0;

	rightFollower.segment = 0;
	rightFollower.last_error = 0;

	sensorSubsystem->ResetPhysicalPose();
	printf("Path ready. Starting periodic.\n");
	SmartDashboard::PutBoolean("Path ready", true);

	StartWorkerThread();
}

void ArcTurnCommand::StartWorkerThread()
{
	//updateNotifier->StartPeriodic(kDT);
	// Try using a thread as the updater, to see if we can get the time to be more
	// reliable.  We can also try increasing its priority using pthread_setschedparam()
	// http://stackoverflow.com/questions/18884510/portable-way-of-setting-stdthread-priority-in-c11

	finished.store(false);
	clock_gettime(CLOCK_MONOTONIC, &startTime);
	lastTime = startTime;

	updateThread = std::thread(WorkerThread, this);

	int policy;
	struct sched_param param;
	pthread_getschedparam(updateThread.native_handle(), &policy, &param);
	logger->Log("Initializing. Policy %d priority %d\n", policy, param.__sched_priority);
	param.__sched_priority = 20;
	pthread_setschedparam(updateThread.native_handle(), SCHED_RR, &param);
}

// Called repeatedly when this Command is scheduled to run
void ArcTurnCommand::Execute() {}


void ArcTurnCommand::WorkerThread(ArcTurnCommand *thisCommand)
{
	long microsecondsPerCycle = rint((((double) 1/150) / 2) * 1000000);
#ifdef	DEBUG_WORKER_THREAD
	printf("Starting worker thread.  Cycle is %ldus\n", microsecondsPerCycle);
#endif
	bool firstTime = true;

	while (!thisCommand->finished.load())
	{
		timespec now;
		clock_gettime(CLOCK_MONOTONIC, &now);

		thisCommand->update();

		long elapsedMicroseconds = TimeUtil::GetElapsedMicroseconds(&thisCommand->lastTime, &now);
		long overrunMicroseconds = elapsedMicroseconds - microsecondsPerCycle;
		long sleepTimeInMicroseconds = 0;
		if (firstTime) {
			sleepTimeInMicroseconds = microsecondsPerCycle;
			firstTime = false;
		} else {
			sleepTimeInMicroseconds = microsecondsPerCycle - overrunMicroseconds;
		}

#ifdef	DEBUG_WORKER_THREAD
		printf("Worker thread: LastTime: %ldus, now: %ldus, elapsed %ldus, overrun: %ldus, sleepTime: %ldus\n", thisCommand->lastTime.tv_nsec / 1000,
				now.tv_nsec / 1000, elapsedMicroseconds, overrunMicroseconds, sleepTimeInMicroseconds);
#endif

		thisCommand->lastTime = now;

		std::chrono::duration<long, std::micro> nanoseconds(sleepTimeInMicroseconds);
		std::this_thread::sleep_for(nanoseconds);
	}

#ifdef	DEBUG_WORKER_THREAD
	printf("Worker thread is exiting.\n");
#endif
	chassis->Stop();
}

void ArcTurnCommand::update() {

	if(finished.load()) {
		chassis->Stop();
		return;
	}

	Pose currentPhysicalPose = sensorSubsystem->GetPhysicalPose();
	timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	long elapsedTimeInMicroseconds = TimeUtil::GetElapsedMicroseconds(&this->startTime, &now);
#ifdef	DEBUG_PATHFINDER
	logger->Log(separator);
	DumpPose(&currentPhysicalPose);
	
	long deltaT = TimeUtil::GetElapsedMicroseconds(&lastTime, &now);
	logger->Log("Tick: %ldus, elapsed: %ldus \n", deltaT, elapsedTimeInMicroseconds);
	lastTime = now;

	SmartDashboard::PutNumber("Tick", deltaT);
#endif

//	pathfinder_follow_distance(leftConfig, &leftFollower, leftTrajectory, length,
//			currentPhysicalPose.GetLeftDistance());
	tbdPathfinder.Follow(leftConfig, &leftFollower, leftTrajectory, length, currentPhysicalPose.GetLeftDistance(),
			elapsedTimeInMicroseconds, kDT, logger);

#ifdef	DEBUG_PATHFINDER
	DumpDistanceFollower("Left", &leftFollower, leftTrajectory, length, currentPhysicalPose.GetLeftVelocity());
#endif

//	pathfinder_follow_distance(rightConfig, &rightFollower, rightTrajectory, length,
//			currentPhysicalPose.GetRightDistance());
	//Make sure to flip the sign of the Right Distance
	tbdPathfinder.Follow(rightConfig, &rightFollower, rightTrajectory, length, currentPhysicalPose.GetRightDistance(),
			elapsedTimeInMicroseconds, kDT, logger);
#ifdef	DEBUG_PATHFINDER
	DumpDistanceFollower("Right", &rightFollower, rightTrajectory, length, currentPhysicalPose.GetRightVelocity());
#endif

	if(leftFollower.finished || rightFollower.finished) {
		finished.store(true);
	}

#ifdef IMU_HEADING_CORRECTION

	// Steve:  looks like heading on both sides is always the same.
	// arc = theta * r => theta = arc/r
	double goalHeading = d2r(leftTrajectory[leftFollower.segment].position / (kCHASSIS_WIDTH/2.0));
	double observedHeading = -currentPhysicalPose.GetHeading();

	double angleDiff = MathUtil::GetDifferenceInAngleDegrees(observedHeading, goalHeading);
	SmartDashboard::PutNumber("Angle Diff", angleDiff);

	double turn = kTurn * angleDiff;
#else
	double turn = 0;
#endif

//	chassis->GetLeftMaster()->Set((leftFollower.output) + turn);
//	chassis->GetRightMaster()->Set((rightFollower.output) - turn);
//	chassis->TankDrive(leftFollower.output + turn, -rightFollower.output - turn); // Flip the right side.
	if(leftDrive) {
		chassis->TankDrive(leftFollower.output + turn, 0); // Flip the right side.
	} else {
		chassis->TankDrive(0, rightFollower.output - turn); // Flip the right side.

	}

	SmartDashboard::PutNumber("Left Pos", leftTrajectory[leftFollower.segment].position);
	SmartDashboard::PutNumber("Left Vel", leftTrajectory[leftFollower.segment].velocity);
	SmartDashboard::PutNumber("Left Accel", leftTrajectory[leftFollower.segment].acceleration);
	SmartDashboard::PutNumber("Left Error", leftFollower.last_error);
	SmartDashboard::PutNumber("Left segment", leftFollower.segment);
	SmartDashboard::PutNumber("Left Follower Out", leftFollower.output);

	SmartDashboard::PutNumber("Right Pos", rightTrajectory[rightFollower.segment].position);
	SmartDashboard::PutNumber("Right Vel", rightTrajectory[rightFollower.segment].velocity);
	SmartDashboard::PutNumber("Right Accel", rightTrajectory[rightFollower.segment].acceleration);
	SmartDashboard::PutNumber("Right Error", rightFollower.last_error);
	SmartDashboard::PutNumber("Right segment", rightFollower.segment);
	SmartDashboard::PutNumber("Right Follower Out", rightFollower.output);
}

// Make this return true when this Command no longer needs to run execute()
bool ArcTurnCommand::IsFinished() {
#ifdef	CALCULATE_ONLY
	printf("PathFinder is in calculate-only mode.  Profile will not be run.\n");
	return true;
#else
	return finished.load();
#endif
}

// Called once after isFinished returns true
void ArcTurnCommand::End() {
	this->cleanUp();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ArcTurnCommand::Interrupted() {
	this->cleanUp();
}

void ArcTurnCommand::StopWorkerThread()
{
#ifdef	DEBUG_WORKER_THREAD
	printf("Stopping thread.\n");
#endif

	finished.store(true);
	updateThread.join();

#ifdef	DEBUG_WORKER_THREAD
	printf("Thread stopped.\n");
#endif
}

void ArcTurnCommand::cleanUp() {
	//updateNotifier->Stop();
	StopWorkerThread();

	delete leftTrajectory;
	delete rightTrajectory;
	delete trajectory;
}

void ArcTurnCommand::DumpCandidate(TrajectoryCandidate candidate)
{
	logger->Log(separator);
	logger->Log("Candidate:");

	logger->Log("  totalLength: %lf\n  length: %d\n", candidate.totalLength, candidate.length);
	logger->Log("  path_length: %d\n", candidate.path_length);

	logger->Log("TrajectoryInfo:\n  filter1: %d\n  filter2: %d\n  length: %d\n",
			candidate.info.filter1, candidate.info.filter2, candidate.info.length);
	logger->Log("  dt: %lf\n  u: %lf\n  v: %lf\n  impulse: %lf\n",
			candidate.info.dt, candidate.info.u, candidate.info.v, candidate.info.impulse);

	logger->Log("TrajectoryConfig:\n");
	logger->Log("  dt: %lf\n  max_v: %lf\n  max_a: %lf\n  max_j: %lf\n  src_v: %lf\n",
			candidate.config.dt, candidate.config.max_v, candidate.config.max_a,
			candidate.config.max_j, candidate.config.src_v);
	logger->Log("  src_theta: %lf\n  dest_pos: %lf\n  dest_v: %lf\n  dest_theta: %lf\n",
			candidate.config.src_theta, candidate.config.dest_pos, candidate.config.dest_v, candidate.config.dest_theta);
	logger->Log("  sample_count: %d\n", candidate.config.sample_count);

	logger->Log("Splines (%d)\n", candidate.path_length);
	for (int spline = 0; spline < candidate.path_length; spline++) {
		logger->Log("Spline %d:\n", spline);
		logger->Log("  a: %lf\n  b: %lf\n  c: %lf\n  d: %lf\n  e: %lf\n",
				candidate.saptr[spline].a,
				candidate.saptr[spline].b,
				candidate.saptr[spline].c,
				candidate.saptr[spline].d,
				candidate.saptr[spline].e);
		logger->Log("  x_offset: %lf\n  y_offset: %lf\n  angle_offset: %lf\n  knot_distance: %lf\n  arc_length: %lf\n",
				candidate.saptr[spline].x_offset,
				candidate.saptr[spline].y_offset,
				candidate.saptr[spline].angle_offset,
				candidate.saptr[spline].knot_distance,
				candidate.saptr[spline].arc_length);
	}

	logger->Log("\n");
}

void ArcTurnCommand::DumpSegments(const char *description, Segment* ideal, Segment* segmentLeft, Segment* segmentRight, int length)
{
	logger->Log(separator);
	logger->Log("%s Segments (%d)\n", description, length);
	for (int i = 0; i < length; i++)
	{
		logger->Log("Segment %d:\n", i);

		logger->Log("  Ideal:  dt: %lf, x: %lf, y: %lf, position: %lf\n  velocity: %lf acceleration: %lf jerk: %lf heading: %lf\n",
				segmentLeft[i].dt,
				segmentLeft[i].x,
				segmentLeft[i].y,
				segmentLeft[i].position,
				segmentLeft[i].velocity,
				segmentLeft[i].acceleration,
				segmentLeft[i].jerk,
				segmentLeft[i].heading
				);

		logger->Log("  Left:   dt: %lf, x: %lf, y: %lf, position: %lf\n  velocity: %lf acceleration: %lf jerk: %lf heading: %lf\n",
				segmentLeft[i].dt,
				segmentLeft[i].x,
				segmentLeft[i].y,
				segmentLeft[i].position,
				segmentLeft[i].velocity,
				segmentLeft[i].acceleration,
				segmentLeft[i].jerk,
				segmentLeft[i].heading
				);

		logger->Log("  Right:  dt: %lf, x: %lf, y: %lf, position: %lf\n  velocity: %lf acceleration: %lf jerk: %lf heading: %lf\n",
				segmentRight[i].dt,
				segmentRight[i].x,
				segmentRight[i].y,
				segmentRight[i].position,
				segmentRight[i].velocity,
				segmentRight[i].acceleration,
				segmentRight[i].jerk,
				segmentRight[i].heading
				);
	}

	logger->Log("\n");
}

void ArcTurnCommand::DumpWaypoints(Waypoint *points, int pointLength)
{
	logger->Log(separator);
	logger->Log("%d waypoints\n",
			pointLength);

	for(int i = 0 ; i < pointLength; i++) {
		logger->Log("Waypoint %d:", i);
		logger->Log("  x: %lf, y: %lf, angle: %lf\n", points[i].x, points[i].y, points[i].angle);
	}

	logger->Log("\n");
}

void ArcTurnCommand::DumpPose(Pose *pose)
{
	logger->Log("Pose:\n");
	logger->Log("  Left  - Distance: %lf, Velocity: %lf\n", pose->GetLeftDistance(), pose->GetLeftVelocity());
	logger->Log("  Right - Distance: %lf, Velocity: %lf\n", pose->GetRightDistance(), pose->GetRightVelocity());
	logger->Log("  Heading: %lf, HeadingVelocity: %lf\n", pose->GetHeading(), pose->GetHeadingVelocity());
	logger->Log("\n");
}

void ArcTurnCommand::DumpDistanceFollower(const char *label, DistanceFollower *follower, Segment* segments,
		int segmentCount, double actualVelocity)
{
	logger->Log("%s DistanceFollower (segment %d/%d)\n", label, follower->segment, segmentCount);
	logger->Log("  output: %lf, last_error (pos): %lf, heading: %lf, velocity error: %lf\n",
			follower->output, follower->last_error, follower->heading,
			actualVelocity - segments[follower->segment].velocity);
	logger->Log("  Segment: position: %lf, heading: %lf, velocity: %lf, acceleration: %lf\n",
			segments[follower->segment].position,
			segments[follower->segment].heading,
			segments[follower->segment].velocity,
			segments[follower->segment].acceleration
			);
	logger->Log("\n");
}

void ArcTurnCommand::WriteSegmentsToCsv(Segment* trajectory, int segmentCount)
{
	FILE *csvFile = fopen("/home/lvuser/lastTrajectory.csv", "w");
	fprintf(csvFile, "dt,x,y,position,velocity,acceleration,jerk,heading\n");

	for (int i = 0; i < segmentCount; i++)
	{
		fprintf(csvFile, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf\n",
				trajectory[i].dt,
				trajectory[i].x,
				trajectory[i].y,
				trajectory[i].position,
				trajectory[i].velocity,
				trajectory[i].acceleration,
				trajectory[i].jerk,
				trajectory[i].heading
				);
	}

	fclose(csvFile);
}

