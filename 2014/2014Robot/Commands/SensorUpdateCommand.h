#ifndef SENSORUPDATECOMMAND_H
#define SENSORUPDATECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author scum
 */
class SensorUpdateCommand: public CommandBase {
public:
	SensorUpdateCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
