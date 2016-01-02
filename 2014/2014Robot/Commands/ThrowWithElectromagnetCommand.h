#ifndef THROWWITHELECTROMAGNETCOMMAND_H
#define THROWWITHELECTROMAGNETCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowWithElectromagnetCommand: public CommandBase {
private:
	Timer *throwTimer;
	float throwTime;
	float electromagnetTime;
	float throwDelay;
	bool isElectromagnetOn;
public:
	ThrowWithElectromagnetCommand();
	ThrowWithElectromagnetCommand(float throwTime, float electromagnetTime);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
