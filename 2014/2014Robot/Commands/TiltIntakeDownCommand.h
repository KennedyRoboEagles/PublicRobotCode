#ifndef TILTINTAKEDOWNCOMMAND_H
#define TILTINTAKEDOWNCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TiltIntakeDownCommand: public CommandBase {
public:
	TiltIntakeDownCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
