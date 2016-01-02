#ifndef THROWANDRETRACTCOMMANDGROUP_H
#define THROWANDRETRACTCOMMANDGROUP_H

#include "Commands/CommandGroup.h"

/**
 *
 *
 * @author nowireless
 */
class ThrowAndRetractCommandGroup: public CommandGroup {
public:	
	ThrowAndRetractCommandGroup();
	ThrowAndRetractCommandGroup(float throwTime);
};

#endif
