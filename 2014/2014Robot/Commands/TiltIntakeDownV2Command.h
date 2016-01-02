#ifndef TILTINTAKEDOWNV2COMMAND_H
#define TILTINTAKEDOWNV2COMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class TiltIntakeDownV2Command: public CommandBase {
private:
	Timer *timer;
public:
	TiltIntakeDownV2Command();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
