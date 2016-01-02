/*
 * PIDSourceEncoderPosition.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#include <Util/PIDSourceEncoderDistance.h>

PIDSourceEncoderDistance::PIDSourceEncoderDistance(Encoder *encoder) {
	this->encoder = encoder;
}

PIDSourceEncoderDistance::~PIDSourceEncoderDistance() {
	// TODO Auto-generated destructor stub
}

double PIDSourceEncoderDistance::PIDGet() {
	return this->encoder->GetDistance();
}
