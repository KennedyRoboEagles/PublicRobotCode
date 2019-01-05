/*
 * RampUtil.cpp
 *
 *  Created on: Mar 11, 2018
 *      Author: nowir
 */

#include <Util/RampUtil.h>

namespace ramputil {

double RampCalc(double rampLength, double current, double initial, double final) {
	return ((rampLength - current) / rampLength * initial) * ((initial - final) / initial) + final;
}
}
