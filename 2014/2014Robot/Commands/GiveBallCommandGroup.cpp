#include "GiveBallCommandGroup.h"
#include "TiltIntakeDownCommand.h"
#include "OpenIntakeCommand.h"
#include "MoveBackwardCommand.h"

//assumes that ball is in grabber and grabber is in up-position

GiveBallCommandGroup::GiveBallCommandGroup() {
      AddSequential(new TiltIntakeDownCommand());
      AddSequential(new OpenIntakeCommand());
      AddSequential(new MoveBackwardCommand(18, .5));
}
