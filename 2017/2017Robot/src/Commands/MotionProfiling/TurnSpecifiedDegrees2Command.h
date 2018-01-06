#ifndef TurnSpecifiedDegrees2Command_H
#define TurnSpecifiedDegrees2Command_H

#include "../../CommandBase.h"
#include "PIDController.h"
#include "PIDOutput.h"
#include "Timer.h"
#include <Util/DiasyFilter/DaisyFilter.h>
#include "RobotConstants.h"

class TurnSpecifiedDegrees2Command : public CommandBase,  PIDOutput {
private:
	enum State {
		kTurning,
		kSteadyState,
		kEnd
	};

	Timer *timer;
	PIDController *controller;
	DaisyFilter *filter;

	double output;
	double goalAngle;

	State state;
	bool finished;
	double timeout;
	double steadyStateStart;
	void cleanUp();

public:
	TurnSpecifiedDegrees2Command(double angle, double timeout = kDEFAULT_TURN_TIMEOUT);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	virtual void PIDWrite(double output);
};

#endif  // TurnSpecifiedDegrees2Command_H
