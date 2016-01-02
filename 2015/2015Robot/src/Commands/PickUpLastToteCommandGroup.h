#ifndef PickUpLastToteCommandGroup_H
#define PickUpLastToteCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class PickUpLastToteCommandGroup: public CommandGroup
{
public:
	PickUpLastToteCommandGroup(float timeBackward, float turnAngle);
};

#endif
