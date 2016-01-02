/*
 * TowerSD.h
 *
 *  Created on: Mar 31, 2015
 *      Author: nowireless
 */

#ifndef SRC_UTIL_TOWERSD_H_
#define SRC_UTIL_TOWERSD_H_

#include <string>
#include <SmartDashboard/NamedSendable.h>

class TowerSD: public NamedSendable {
public:
	TowerSD();
	virtual ~TowerSD();

	std::string GetName();
	void InitTable(ITable *subtable);
	ITable *GetTable();
	std::string GetSmartDashboardType();

	void UpdateState(std::string state);
	void UpdateLimits(bool upper, bool lower);
	void Update(std::string positon, double forceVoltage, bool atPosition, double setPoint, double currentPosition, double delta);
private:
	ITable *table;
};

#endif /* SRC_UTIL_TOWERSD_H_ */
