#ifndef WAITFORHOTGOALCOMMAND_H
#define WAITFORHOTGOALCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class WaitForHotGoalCommand: public CommandBase {
private:
	Timer *timer;
	float timeout;
	float lastProcessTime;
public:
	WaitForHotGoalCommand();
	WaitForHotGoalCommand(float timeout);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
