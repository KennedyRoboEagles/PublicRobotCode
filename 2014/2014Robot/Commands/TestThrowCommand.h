#ifndef TESTTHROWCOMMAND_H
#define TESTTHROWCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TestThrowCommand: public CommandBase {
public:
	TestThrowCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
