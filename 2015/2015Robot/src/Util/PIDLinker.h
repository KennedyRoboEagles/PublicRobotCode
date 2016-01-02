/*
 * PIDLinker.h
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#ifndef SRC_UTIL_PIDLINKER_H_
#define SRC_UTIL_PIDLINKER_H_

#include <PIDOutput.h>
#include <PIDController.h>

class PIDLinker: public PIDOutput {
private:
	PIDController *controller;
public:
	PIDLinker(PIDController *controller);
	virtual ~PIDLinker();

	void PIDWrite(float output);
};

#endif /* SRC_UTIL_PIDLINKER_H_ */
