/*
 * SimpleVision.h
 *
 *  Created on: Mar 27, 2014
 *      Author: nowireless
 */

#ifndef SIMPLEVISION_H_
#define SIMPLEVISION_H_

#include <Vision/ColorImage.h>

class SimpleVision {
public:
	SimpleVision();
	virtual ~SimpleVision();
	bool IsHotGoal(ColorImage *image, int hMin, int hMax, int sMin, int sMax, int vMin, int vMax);
};

#endif /* SIMPLEVISION_H_ */
