#include "ThrowAndRetractCommandGroup.h"
#include "ThrowCommand.h"
#include "RetractCommand.h"
#include "ThrowWithElectromagnetCommandV2.h"

#define THROWER_GRACE_PERIOD (0.2)

ThrowAndRetractCommandGroup::ThrowAndRetractCommandGroup() {
    AddSequential(new ThrowWithElectromagnetCommandV2());
    AddSequential(new WaitCommand(THROWER_GRACE_PERIOD));
    AddSequential(new RetractCommand());
}

ThrowAndRetractCommandGroup::ThrowAndRetractCommandGroup(float throwTime) {
    AddSequential(new ThrowCommand(throwTime));
    AddSequential(new WaitCommand(THROWER_GRACE_PERIOD));
    AddSequential(new RetractCommand());
	
}
