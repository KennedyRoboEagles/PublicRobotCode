/*
 * LidarLiteI2C.h
 *
 *  Created on: Jan 19, 2015
 *      Author: nowireless
 */

#ifndef SRC_SENSORS_LIDARLITEI2C_H_
#define SRC_SENSORS_LIDARLITEI2C_H_

#include <I2C.h>

class LidarLite_I2C : public I2C {
protected:
	static const uint8_t kAddress = 0x62;
	static const uint8_t kRegisterMeasure = 0x00;
	static const uint8_t kMeasureValue = 0x04;
	static const uint8_t kRegisterHighLowB = 0x8f;
public:
	LidarLite_I2C(Port port);
	virtual ~LidarLite_I2C();

	int GetDistance();
};

#endif /* SRC_SENSORS_LIDARLITEI2C_H_ */
