#ifndef SWAPCOMMANDCOMMAND_H
#define SWAPCOMMANDCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class SwapCommandCommand: public CommandBase {
private:
	bool swapState;
	int runCount;
	Command *commandOne;
	Command *commandTwo;
	Command *runningCommand;
public:
	SwapCommandCommand(Command *commandOne, Command *commandTwo);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
	void Reset();
};

#endif
