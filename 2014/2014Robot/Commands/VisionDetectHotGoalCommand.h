#ifndef VISIONDETECTHOTGOALCOMMAND_H
#define VISIONDETECTHOTGOALCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class VisionDetectHotGoalCommand: public CommandBase {
public:
	VisionDetectHotGoalCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
