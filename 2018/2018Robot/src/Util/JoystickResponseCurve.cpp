/*
 * JoystickResponseCurve.cpp
 *
 *  Created on: Mar 13, 2018
 *      Author: nowir
 */

#include <Util/JoystickResponseCurve.h>
#include <cmath>


JoystickResponseCurve::JoystickResponseCurve(double adj, double pow, double mult, double dead) :
	adjust_(adj),
	power_(pow),
	multiplier_(mult),
	deadzone_(dead) {}

double JoystickResponseCurve::Transform(double input) {
	double output = 0.0;
	if(deadzone_ < fabs(input)) {
		output = multiplier_ * (adjust_ * pow(input, power_) + (1 - adjust_) * input);
	}
	return output;
}
