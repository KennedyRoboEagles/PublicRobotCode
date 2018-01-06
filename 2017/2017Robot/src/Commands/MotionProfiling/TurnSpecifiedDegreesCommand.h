#ifndef TURNSPECIFIEDDEGREESCOMMAND_H
#define TURNSPECIFIEDDEGREESCOMMAND_H

#include "../../CommandBase.h"
#include <Timer.h>

/**
 *
 *
 * @author speterson
 */
class TurnSpecifiedDegreesCommand: public CommandBase {
private:
	double goalAngle;
	bool finished;
	frc::Timer *timer;

	void cleanUp();

public:
	TurnSpecifiedDegreesCommand(double degreesToTurn);
	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();
};

#endif
