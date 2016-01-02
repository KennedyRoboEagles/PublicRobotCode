#ifndef TESTRETRACTCOMMAND_H
#define TESTRETRACTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TestRetractCommand: public CommandBase {
public:
	TestRetractCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
