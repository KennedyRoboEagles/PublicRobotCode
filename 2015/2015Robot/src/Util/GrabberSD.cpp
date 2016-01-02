/*
 * GrabberSD.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: nowireless
 */

#include <Util/GrabberSD.h>
#include <DriverStation.h>

GrabberSD::GrabberSD() {
	this->table = NULL;
}

GrabberSD::~GrabberSD() {
}

std::string GrabberSD::GetName() {
	return "Grabber";
}

void GrabberSD::InitTable(ITable *subtable) {
	this->table = subtable;
}

ITable *GrabberSD::GetTable() {
	return this->table;
}

std::string GrabberSD::GetSmartDashboardType() {
	return "Grabber";
}

void GrabberSD::UpdateState(std::string state) {
	if(this->table != NULL) {
		this->table->PutString("State", state);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}
}

void GrabberSD::UpdatePosition(std::string position) {
	if(this->table != NULL) {
		this->table->PutString("Position", position);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}
}

void GrabberSD::UpdateCurrentDraw(double draw) {
	if(this->table != NULL) {
		this->table->PutNumber("Current Draw", draw);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}

}

void GrabberSD::UpdateSetpoint(double setpoint) {
	if(this->table != NULL) {
		this->table->PutNumber("Setpoint", setpoint);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}
}

void GrabberSD::UpdateCurrentPosition(double pos) {
	if(this->table != NULL) {
		this->table->PutNumber("Current Position", pos);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}
}

void GrabberSD::UpdateDelta(double delta) {
	if(this->table != NULL) {
		this->table->PutNumber("Delta", delta);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}
}

void GrabberSD::UpdateIsDone(bool done) {
	if(this->table != NULL) {
		this->table->PutBoolean("Is Done", done);
	} else {
		DriverStation::GetInstance()->ReportError("Grabber Table is NULL");
	}

}
