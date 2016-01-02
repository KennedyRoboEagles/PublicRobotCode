/*
 * LidarLiteI2C.cpp
 *
 *  Created on: Jan 19, 2015
 *      Author: nowireless
 */

#include <Sensors/LidarLiteI2C.h>

/*
 * Based on:
 * https://github.com/PulsedLight3D/LIDARLite_Basics/blob/master/
 * 	Arduino/LIDARLite_I2C_Library_GetDistance_ContinuousRead/
 * 	LIDARLite_I2C_Library_GetDistance_ContinuousRead.ino
 *
 */
LidarLite_I2C::LidarLite_I2C(Port port) : I2C(port, kAddress) {
	bool abourted = Write(kRegisterMeasure, kMeasureValue);
	if(abourted) {
		printf("Lidar Measure Write Failed\n");
	}
}

LidarLite_I2C::~LidarLite_I2C() {}

int LidarLite_I2C::GetDistance() {
	uint8_t buffer[2];
	Read(kRegisterHighLowB, 2, buffer);
	return (buffer[0] << 8) + buffer[1];
}
