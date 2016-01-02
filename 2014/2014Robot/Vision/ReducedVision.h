/*
 * ReducedVision.h
 *
 *  Created on: Mar 27, 2014
 *      Author: nowireless
 */

#ifndef REDUCEDVISION_H_
#define REDUCEDVISION_H_

#include "Vision/ColorImage.h"

class ReducedVision {
public:
	ReducedVision();
	virtual ~ReducedVision();
	bool HotTargetVisable(ColorImage *image);
};

#endif /* REDUCEDVISION_H_ */
