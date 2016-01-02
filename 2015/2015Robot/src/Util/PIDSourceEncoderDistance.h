/*
 * PIDSourceEncoderPosition.h
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#ifndef SRC_UTIL_PIDSOURCEENCODERDISTANCE_H_
#define SRC_UTIL_PIDSOURCEENCODERDISTANCE_H_

#include "PIDSource.h"
#include "Encoder.h"

class PIDSourceEncoderDistance : public PIDSource {
private:
	Encoder *encoder;
public:
	PIDSourceEncoderDistance(Encoder *encoder);
	virtual ~PIDSourceEncoderDistance();
	double PIDGet();
};

#endif /* SRC_UTIL_PIDSOURCEENCODERDISTANCE_H_ */
