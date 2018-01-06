/*
 * TimeUtil.cpp
 *
 *  Created on: Feb 10, 2017
 *      Author: steve
 */

#include <Util/TimeUtil.h>
#include <stdint.h>

long TimeUtil::GetElapsedMicroseconds(struct timespec* start, struct timespec* end)
{
		return ((end->tv_sec - start->tv_sec) * 1000000) + (end->tv_nsec - start->tv_nsec) / 1000;
}
