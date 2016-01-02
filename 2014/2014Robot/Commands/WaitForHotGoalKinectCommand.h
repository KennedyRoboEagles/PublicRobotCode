#ifndef WAITFORHOTGOALKINECTCOMMAND_H
#define WAITFORHOTGOALKINECTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class WaitForHotGoalKinectCommand: public CommandBase {
private:
	Timer *timer;
public:
	WaitForHotGoalKinectCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
