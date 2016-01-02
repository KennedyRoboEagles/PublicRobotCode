#include "GrabAndThrowCommandGroup.h"
#include "ThrowCommand.h"
#include "RetractCommand.h"
#include "TiltIntakeDownCommand.h"
#include "TiltIntakeUpCommand.h"
#include "OpenIntakeCommand.h"
#include "CloseIntakeCommand.h"
#include "TurnSpecifiedDegreesCommand.h"

#define THROWER_GRACE_PERIOD .1

//assumes that there is a ball in the grabber

GrabAndThrowCommandGroup::GrabAndThrowCommandGroup() {
	AddSequential(new RetractCommand());
    AddSequential(new TiltIntakeUpCommand());
    AddSequential(new OpenIntakeCommand());
    AddSequential(new TiltIntakeDownCommand());
    AddSequential(new ThrowCommand());
    AddSequential(new WaitCommand(THROWER_GRACE_PERIOD));
    AddSequential(new TiltIntakeUpCommand());
    AddSequential(new TurnSpecifiedDegreesCommand(90));
}

GrabAndThrowCommandGroup::GrabAndThrowCommandGroup(float throwTime) {
	AddSequential(new RetractCommand());
    AddSequential(new TiltIntakeUpCommand());
    AddSequential(new OpenIntakeCommand());
    AddSequential(new TiltIntakeDownCommand());
    AddSequential(new ThrowCommand(throwTime));
    AddSequential(new WaitCommand(THROWER_GRACE_PERIOD));
    AddSequential(new TiltIntakeUpCommand());
    AddSequential(new TurnSpecifiedDegreesCommand(90));
}
