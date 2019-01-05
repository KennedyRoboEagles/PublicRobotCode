/*
 * GenericPIDSource.cpp
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#include <Util/GenericPIDSource.h>

GenericPIDSource::GenericPIDSource() : value_(0) {}
GenericPIDSource::~GenericPIDSource() {}
void GenericPIDSource::Set(double value) {
	value_ = value;
}

double GenericPIDSource::PIDGet() {
	return value_;
}
