#ifndef TESTMOVESTRAIGHTCOMMAND_H
#define TESTMOVESTRAIGHTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TestMoveStraightCommand: public CommandBase {
private:
	int leftStartingCount;
	int rightStartingCount;
	float leftSetPoint;
	float rightSetPoint;
	bool isLeftDone;
	bool isRightDone;
	float distance;
	float distanceTicks;
public:
	TestMoveStraightCommand(float inches);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
