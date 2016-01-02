#ifndef MOVEFORWARDCOMMAND_H
#define MOVEFORWARDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class MoveForwardCommand: public CommandBase {
private:
	float speed;
	int distance;
	float distanceTicks;
	float encoderSetpoint;
	float delta;
public:
	MoveForwardCommand(int inches, float speed);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
