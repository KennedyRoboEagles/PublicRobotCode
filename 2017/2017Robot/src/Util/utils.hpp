/*
 * https://github.com/Team254/FRC-2012/tree/master/src/config
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <math.h>

/**
 * @author Eric Bakan
 * Useful functions which are repeated across classes
 */

/**
 * Implements a deadband on a joystick
 * @param val the joystick value
 * @param deadband the maximum value the deadband will return 0 for
 * @return 0.0 if the absolute value of the joystick value is less than the deadband, else the joystick value
 */
inline double HandleDeadband(double val, double deadband) {
  return (fabs(val) > fabs(deadband)) ? val : 0.0;
}

#endif // UTILS_HPP_
