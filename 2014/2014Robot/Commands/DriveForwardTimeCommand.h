#ifndef DRIVEFORWARDTIMECOMMAND_H
#define DRIVEFORWARDTIMECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class DriveForwardTimeCommand: public CommandBase {
private:
	Timer *timer;
	float time;
	float speed;
	void cleanUp();
public:
	DriveForwardTimeCommand(float seconds, float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
