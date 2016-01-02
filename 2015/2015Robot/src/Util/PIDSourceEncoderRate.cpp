/*
 * PIDSourceEncoderRate.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#include <Util/PIDSourceEncoderRate.h>

PIDSourceEncoderRate::PIDSourceEncoderRate(Encoder *encoder) {
	// TODO Auto-generated constructor stub
	this->encoder = encoder;

}

PIDSourceEncoderRate::~PIDSourceEncoderRate() {
	// TODO Auto-generated destructor stub
}

double PIDSourceEncoderRate::PIDGet() {
	return this->encoder->GetRate();
}
