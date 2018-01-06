/*
 * Pose.h
 *
 *  Created on: Jan 17, 2017
 *      Author: Ryan
 */

#ifndef SRC_UTIL_POSE_H_
#define SRC_UTIL_POSE_H_

class Pose {
public:
	Pose(double leftDistance, double rightDistance,
			double leftVelocity, double rightVelocity,
			double heading, double headingVelocity);
	virtual ~Pose();

	void Reset(double leftDistance, double rightDistance,
			double leftVelocity, double rightVelocity,
			double heading, double headingVelocity);

	double GetLeftDistance();
	double GetRightDistance();

	double GetLeftVelocity();
	double GetRightVelocity();

	double GetHeading();
	double GetHeadingVelocity();

private:
	double leftDistance;
	double rightDistance;
	double leftVelocity;
	double rightVelocity;
	double heading;
	double headingVelocity;

};

#endif /* SRC_UTIL_POSE_H_ */
