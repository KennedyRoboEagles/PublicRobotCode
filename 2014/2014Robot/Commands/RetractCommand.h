#ifndef RETRACTCOMMAND_H
#define RETRACTCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class RetractCommand: public CommandBase {
public:
	RetractCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
