/*
 * SimpleVision.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: nowireless
 */

#include "SimpleVision.h"
#include <nivision.h>

#define PIXEL_THRESHOLD (500)

SimpleVision::SimpleVision() {
	// TODO Auto-generated constructor stub

}

SimpleVision::~SimpleVision() {
	// TODO Auto-generated destructor stub
}

bool SimpleVision::IsHotGoal(ColorImage *image, int hMin, int hMax, int sMin, int sMax, int vMin, int vMax) {
	BinaryImage *thresholdImage = image->ThresholdHSV(hMin, hMax, sMin, sMax, vMin, vMax);
	ImageInfo imageInfo;
	Image *imaqImage = thresholdImage->GetImaqImage();
	imaqGetImageInfo(imaqImage, &imageInfo);

	int pixelCount = 0;
	unsigned char *pixels = (unsigned char *) imageInfo.imageStart;

	for (int y = 0; y < imageInfo.yRes; y++) {
		for (int x = 0; x < imageInfo.xRes; x++) {
			int bitmapIndex = (imageInfo.pixelsPerLine *y) + x;
			  if (pixels[bitmapIndex] == 1) {
			        pixelCount++;
			  }
		}
	}
	printf("[SimpleVision] Pixel Count: %i\n", pixelCount);
	delete thresholdImage;

	return pixelCount >= PIXEL_THRESHOLD;
}
