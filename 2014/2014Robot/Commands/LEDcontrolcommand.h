#ifndef LEDCONTROLCOMMAND_H
#define LEDCONTROLCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author scum
 */
class LEDcontrolcommand: public CommandBase {
private:
	int count;
	
public:
	LEDcontrolcommand();
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
