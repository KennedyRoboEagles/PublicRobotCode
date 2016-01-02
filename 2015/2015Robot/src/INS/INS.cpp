/*
 * INS.cpp
 *
 *  Created on: Feb 22, 2015
 *      Author: nowireless
 */

#include <INS/INS.h>
#include <Task.h>
#include <HAL/cpp/Synchronized.hpp>

static ReentrantSemaphore kINSStateSemaphore;

const double LITTLE_G = 9.80665; // Meters/Second ^2

INS *INS::instnace = NULL;

INS *INS::GetInstance() {
	if(instnace == NULL) {
		instnace = new INS();
	}
	return instnace;
}

INS::INS() {
	this->ins = new INSBase(kINSUpdateFrequency);
	this->enabled = false;
	this->mouse = new UsbMouseMovement();
}

INSBase *INS::GetINSBase() {
	return this->ins;
}

UsbMouseMovement *INS::GetMouse() {
	return this->mouse;
}

void INS::SetIsMoving(bool moving) {
	Synchronized sync(kINSStateSemaphore);
	this->ins->SetIsMoving(moving);
}

double INS::GetPositionX() {
	Synchronized sync(kINSStateSemaphore);
	return this->ins->GetPositionX();
}

double INS::GetPositionY() {
	Synchronized sync(kINSStateSemaphore);
	return this->ins->GetPositionY();
}

double INS::GetVelocityX() {
	Synchronized sync(kINSStateSemaphore);
	return this->ins->GetVelocityX();
}

double INS::GetVelocityY() {
	Synchronized sync(kINSStateSemaphore);
	return this->ins->GetVelocityY();
}

bool INS::IsMoving() {
	Synchronized sync(kINSStateSemaphore);
	return this->ins->IsMoving();
}

void INS::SetXAccelThreshold(double threshold) {
	Synchronized sync(kINSStateSemaphore);
	this->ins->SetXAccelThreshold(threshold);
}

void INS::SetYAccelThreshold(double threshold) {
	Synchronized sync(kINSStateSemaphore);
	this->ins->SetYAccelThreshold(threshold);
}

void INS::Enable() {
	Synchronized sync(kINSStateSemaphore);
	this->enabled = true;
	this->mouse->SetEnabled(true);
}

void INS::Disable() {
	Synchronized sync(kINSStateSemaphore);
	this->enabled = false;
	this->mouse->SetEnabled(true);
}

bool INS::IsEnabled() {
	Synchronized sync(kINSStateSemaphore);
	return this->enabled;
}

void INS::Reset() {
	Synchronized sync(kINSStateSemaphore);
	this->ins->Reset();
}

void INS::Update(double xAccel, double yAccel) {

	double xAccelms2 = xAccel * LITTLE_G;
	double yAccelms2 = yAccel * LITTLE_G;

	CRITICAL_REGION(kINSStateSemaphore)
		this->ins->SetIsMoving(this->mouse->IsMoving());
		this->ins->Update(xAccelms2, yAccelms2);
	END_REGION

}
