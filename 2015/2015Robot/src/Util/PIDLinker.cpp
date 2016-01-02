/*
 * PIDLinker.cpp
 *
 *  Created on: Mar 18, 2015
 *      Author: nowireless
 */

#include <Util/PIDLinker.h>

PIDLinker::PIDLinker(PIDController *controller) {
	this->controller = controller;
}

PIDLinker::~PIDLinker() {
	// TODO Auto-generated destructor stub
}

void PIDLinker::PIDWrite(float output) {
	this->controller->SetSetpoint(output);
}

