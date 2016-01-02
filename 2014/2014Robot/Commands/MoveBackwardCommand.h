#ifndef MOVEBACKWARDCOMMAND_H
#define MOVEBACKWARDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class MoveBackwardCommand: public CommandBase {
	float speed;
	int distance;
	float distanceTicks;
	float encoderSetpoint;
	float delta;
public:
	MoveBackwardCommand(int inches, float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
