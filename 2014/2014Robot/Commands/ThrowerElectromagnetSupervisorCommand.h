#ifndef THROWERELECTROMAGNETSUPERVISORCOMMAND_H
#define THROWERELECTROMAGNETSUPERVISORCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowerElectromagnetSupervisorCommand: public CommandBase {
private:
	Timer *timer;
public:
	ThrowerElectromagnetSupervisorCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
