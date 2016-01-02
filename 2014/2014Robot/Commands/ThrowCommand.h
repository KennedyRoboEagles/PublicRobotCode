#ifndef THROWCOMMAND_H
#define THROWCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowCommand: public CommandBase {
private:
	Timer *throwTimer;
	
	float ThrowingTime;
public:
	ThrowCommand();
	ThrowCommand(float throwingTime);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
