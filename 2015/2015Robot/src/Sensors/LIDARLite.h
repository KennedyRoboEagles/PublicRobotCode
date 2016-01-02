/*
 * LIDARLite.h
 *
 *  Created on: Feb 8, 2015
 *      Author: Steve
 */

#ifndef SRC_SENSORS_LIDARLITE_H_
#define SRC_SENSORS_LIDARLITE_H_

#include "WPILib.h"

class LIDARLite: public PIDSource {
public:
	LIDARLite(I2C::Port port);
	virtual ~LIDARLite();
	int GetDistance();
	double PIDGet();
	void Start();
	void Stop();
	void Update();

private:
	const int LIDAR_ADDR = 0x62;
	const int LIDAR_CONFIG_REGISTER = 0x00;
	const int LIDAR_DISTANCE_REGISTER = 0x8f;

	static const int NS_PER_MS = 1000000 * 10;
	const int RETRIES = 10;

	const int LIDAR_MEASURE = 0x04;
	I2C *Lidar;
	Notifier *updateNotifier;
	int distance = 0;
	unsigned char readBytes[2];
	MUTEX_ID semaphore;
	static void CallReadValue(void *lidarLite);
	static void i2cSleep();
	void ReadValue();
};

#endif /* SRC_SENSORS_LIDARLITE_H_ */
