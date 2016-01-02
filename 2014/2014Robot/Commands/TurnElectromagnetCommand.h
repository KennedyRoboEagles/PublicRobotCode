#ifndef TURNELECTROMAGNETCOMMAND_H
#define TURNELECTROMAGNETCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TurnElectromagnetCommand: public CommandBase {
public:
	TurnElectromagnetCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
