#include "GrabAndShootWithHotGoalDetectCommandGroup.h"
#include "OpenIntakeCommand.h"
#include "TiltIntakeDownCommand.h"
#include "TiltIntakeUpCommand.h"
#include "ThrowCommand.h"
#include "TurnSpecifiedDegreesCommand.h"
#include "WaitForHotGoalCommand.h"

#define THROWER_GRACE_PERIOD .1

//assumes ball is in grabber

GrabAndShootWithHotGoalDetectCommandGroup::GrabAndShootWithHotGoalDetectCommandGroup() {
	AddSequential(new TiltIntakeUpCommand());
	        AddSequential(new OpenIntakeCommand());
	        AddSequential(new TiltIntakeDownCommand());
	        AddSequential(new WaitForHotGoalCommand());
	        AddSequential(new ThrowCommand());
	        AddSequential(new WaitCommand(THROWER_GRACE_PERIOD));
	        AddSequential(new TiltIntakeUpCommand());
	        AddSequential(new TurnSpecifiedDegreesCommand(90));
}
