/*
 * TimeUtil.h
 *
 *  Created on: Feb 10, 2017
 *      Author: steve
 */

#ifndef SRC_UTIL_TIMEUTIL_H_
#define SRC_UTIL_TIMEUTIL_H_

#include <time.h>

class TimeUtil {
public:
	static long GetElapsedMicroseconds(struct timespec* start, struct timespec* end);
};

#endif /* SRC_UTIL_TIMEUTIL_H_ */
