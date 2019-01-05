/*
 * JoystickResponseCurve.h
 *
 *  Created on: Mar 13, 2018
 *      Author: nowir
 */

#ifndef SRC_UTIL_JOYSTICKRESPONSECURVE_H_
#define SRC_UTIL_JOYSTICKRESPONSECURVE_H_

class JoystickResponseCurve {
private:
	double adjust_;
	double power_;
	double multiplier_;
	double deadzone_;
public:
	JoystickResponseCurve(double adj, double pow, double mult, double dead);
	double Transform(double input);
};

#endif /* SRC_UTIL_JOYSTICKRESPONSECURVE_H_ */
