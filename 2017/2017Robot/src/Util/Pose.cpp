/*
 * Pose.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: Ryan
 */

#include <Util/Pose.h>

Pose::Pose(double leftDistance, double rightDistance,
			double leftVelocity, double rightVelocity,
			double heading, double headingVelocity) {
	this->leftDistance = leftDistance;
	this->rightDistance = rightDistance;
	this->leftVelocity = leftVelocity;
	this->rightVelocity = rightVelocity;
	this->heading = heading;
	this->headingVelocity = headingVelocity;
}

Pose::~Pose() {
}

void Pose::Reset(double leftDistance, double rightDistance,
			double leftVelocity, double rightVelocity,
			double heading, double headingVelocity) {
	this->leftDistance = leftDistance;
	this->rightDistance = rightDistance;
	this->leftVelocity = leftVelocity;
	this->rightVelocity = rightVelocity;
	this->heading = heading;
	this->headingVelocity = headingVelocity;
}

double Pose::GetLeftDistance() {
	return leftDistance;
}

double Pose::GetRightDistance() {
	return rightDistance;
}

double Pose::GetLeftVelocity() {
	return leftVelocity;
}

double Pose::GetRightVelocity() {
	return rightVelocity;
}

double Pose::GetHeading() {
	return heading;
}

double Pose::GetHeadingVelocity() {
	return headingVelocity;
}
