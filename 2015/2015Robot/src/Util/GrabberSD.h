/*
 * GrabberSD.h
 *
 *  Created on: Apr 1, 2015
 *      Author: nowireless
 */

#ifndef SRC_UTIL_GRABBERSD_H_
#define SRC_UTIL_GRABBERSD_H_

#include <string>
#include <SmartDashboard/NamedSendable.h>

class GrabberSD : public NamedSendable {
private:
	ITable *table;
public:
	GrabberSD();
	virtual ~GrabberSD();

	std::string GetName();
	void InitTable(ITable *subtable);
	ITable *GetTable();
	std::string GetSmartDashboardType();

	void UpdateState(std::string state);
	void UpdatePosition(std::string position);
	void UpdateCurrentDraw(double draw);
	void UpdateSetpoint(double setpoint);
	void UpdateCurrentPosition(double pos);
	void UpdateDelta(double delta);
	void UpdateIsDone(bool done);
};

#endif /* SRC_UTIL_GRABBERSD_H_ */
