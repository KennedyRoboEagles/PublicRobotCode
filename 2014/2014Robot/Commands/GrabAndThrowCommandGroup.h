#ifndef GRABANDTHROWCOMMANDGROUP_H
#define GRABANDTHROWCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author scum
 */
class GrabAndThrowCommandGroup: public CommandGroup {
public:	
	GrabAndThrowCommandGroup();
	GrabAndThrowCommandGroup(float throwTime);
};

#endif
