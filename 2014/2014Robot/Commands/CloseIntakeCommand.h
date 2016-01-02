#ifndef CLOSEINTAKECOMMAND_H
#define CLOSEINTAKECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class CloseIntakeCommand: public CommandBase {
public:
	CloseIntakeCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
