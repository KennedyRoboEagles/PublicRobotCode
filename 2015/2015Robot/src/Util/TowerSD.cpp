/*
 * TowerSD.cpp
 *
 *  Created on: Mar 31, 2015
 *      Author: nowireless
 */

#include <Util/TowerSD.h>
#include <DriverStation.h>

TowerSD::TowerSD() {
	// TODO Auto-generated constructor stub

}

TowerSD::~TowerSD() {
	this->table = NULL;
}

std::string TowerSD::GetName() {
	return "Tower";
}

void TowerSD::InitTable(ITable *subtable) {
	this->table = subtable;
}

ITable *TowerSD::GetTable() {
	return this->table;
}

std::string TowerSD::GetSmartDashboardType() {
	return "Tower";
}

void TowerSD::Update(std::string positon, double forceVoltage, bool atPosition, double setPoint, double currentPosition, double delta) {
	if(this->table != NULL) {
		table->PutString("Position", positon);
		table->PutNumber("Force Voltage", forceVoltage);
		table->PutBoolean("At Position", atPosition);
		table->PutNumber("Setpoint", setPoint);
		table->PutNumber("Current Position", currentPosition);
		table->PutNumber("Delta", delta);

	} else {
		DriverStation::GetInstance()->ReportError("Tower Table is NULL");
	}
}

void TowerSD::UpdateState(std::string state) {
	if(this->table != NULL) {
		table->PutString("State", state);
	} else {
		DriverStation::GetInstance()->ReportError("Tower Table is NULL");
	}
}

void TowerSD::UpdateLimits(bool upper, bool lower) {
	if(this->table != NULL) {
		table->PutBoolean("Upper Limit", upper);
		table->PutBoolean("Lower Limit", lower);
	} else {
		DriverStation::GetInstance()->ReportError("Tower Table is NULL");
	}
}
