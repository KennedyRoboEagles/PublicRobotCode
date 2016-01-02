#ifndef TESTINTAKEOPENCOMMAND_H
#define TESTINTAKEOPENCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TestIntakeOpenCommand: public CommandBase {
public:
	TestIntakeOpenCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
