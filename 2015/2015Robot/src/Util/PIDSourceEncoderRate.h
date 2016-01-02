/*
 * PIDSourceEncoderRate.h
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#ifndef SRC_UTIL_PIDSOURCEENCODERRATE_H_
#define SRC_UTIL_PIDSOURCEENCODERRATE_H_

#include "PIDSource.h"
#include "Encoder.h"

class PIDSourceEncoderRate : public PIDSource {
private:
	Encoder *encoder;
public:
	PIDSourceEncoderRate(Encoder *encoder);
	virtual ~PIDSourceEncoderRate();

	double PIDGet();
};

#endif /* SRC_UTIL_PIDSOURCEENCODERRATE_H_ */
