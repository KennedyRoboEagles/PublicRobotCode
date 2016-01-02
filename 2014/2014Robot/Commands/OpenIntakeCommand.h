#ifndef OPENINTAKECOMMAND_H
#define OPENINTAKECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class OpenIntakeCommand: public CommandBase {
public:
	OpenIntakeCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
