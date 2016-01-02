#ifndef TESTINTAKETILTUPCOMMAND_H
#define TESTINTAKETILTUPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author scum
 */
class TestIntakeTiltUpCommand: public CommandBase {
public:
	TestIntakeTiltUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
