/*
 * MathUtil.h
 *
 *  Created on: Jan 17, 2017
 *      Author: Ryan
 */

#ifndef SRC_UTIL_MATHUTIL_H_
#define SRC_UTIL_MATHUTIL_H_

namespace MathUtil {
	double GetDifferenceInAngleDegrees(double from, double to);
	double BoundAngleNeg180To180Degrees(double angle);
};

#endif /* SRC_UTIL_MATHUTIL_H_ */
