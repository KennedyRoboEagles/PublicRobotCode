#ifndef DRIVEFORWARDPIDCOMMAND_H
#define DRIVEFORWARDPIDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class DriveDistancePIDCommand: public CommandBase, PIDOutput {
private:
	PIDController *controller;
	float setpoint;
	float speed;
	int distance;
public:
	DriveDistancePIDCommand(int distance);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	virtual void PIDWrite(float output);
	void cleanUp();
};

#endif
