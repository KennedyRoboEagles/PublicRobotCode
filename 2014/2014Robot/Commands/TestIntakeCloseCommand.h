#ifndef TESTINTAKECLOSECOMMAND_H
#define TESTINTAKECLOSECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TestIntakeCloseCommand: public CommandBase {
public:
	TestIntakeCloseCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
