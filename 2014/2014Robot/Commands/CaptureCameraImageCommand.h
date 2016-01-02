#ifndef CAPTURECAMERAIMAGECOMMAND_H
#define CAPTURECAMERAIMAGECOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author nowireless
 */
class CaptureCameraImageCommand: public CommandBase {
public:
	CaptureCameraImageCommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
