#ifndef TurnInPlaceCommand_H
#define TurnInPlaceCommand_H

#include "CommandBase.h"
#include <PIDController.h>
#include <Timer.h>

class RotateToAngle : public CommandBase {
public:
	RotateToAngle(double goal);
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();
private:
	enum State {
		kRun,
		kSteadyState,
		kDone
	};

	frc::Timer timer_;
	frc::PIDController* controller_;
	double goal_;
	State state_;
};

#endif  // TurnInPlaceCommand_H
