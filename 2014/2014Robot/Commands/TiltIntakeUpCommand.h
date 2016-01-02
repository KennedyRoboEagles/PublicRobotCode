#ifndef TILTINTAKEUPCOMMAND_H
#define TILTINTAKEUPCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TiltIntakeUpCommand: public CommandBase {
public:
	TiltIntakeUpCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
