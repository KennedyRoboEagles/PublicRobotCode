/*
 * MathUtil.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: Ryan
 */

#include <Util/MathUtil.h>

//https://github.com/Team254/FRC-2015/src/com/team254/lib/util/ChezyMath.java

double MathUtil::GetDifferenceInAngleDegrees(double from, double to) {
	return BoundAngleNeg180To180Degrees(to-from);
}

double MathUtil::BoundAngleNeg180To180Degrees(double angle) {
	// Naive algorithm
	while (angle >= 180.0) {
		angle -= 360.0;
	}
	while (angle < -180.0) {
		angle += 360.0;
	}
	return angle;
}
