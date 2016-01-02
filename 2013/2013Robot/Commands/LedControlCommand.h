#ifndef LEDCONTROLCOMMAND_H
#define LEDCONTROLCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author speterson
 */
class LedControlCommand: public CommandBase {
private:
	int count;
public:
	LedControlCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
