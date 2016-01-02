#ifndef TESTINTAKETILTDOWNCOMMAND_H
#define TESTINTAKETILTDOWNCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author scum
 */
class TestIntakeTiltDownCommand: public CommandBase {
public:
	TestIntakeTiltDownCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
