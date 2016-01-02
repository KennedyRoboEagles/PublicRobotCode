#ifndef THROWWITHELECTROMAGNETCOMMANDV2_H
#define THROWWITHELECTROMAGNETCOMMANDV2_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowWithElectromagnetCommandV2: public CommandBase {
private:
	Timer *timer;
public:
	ThrowWithElectromagnetCommandV2();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
