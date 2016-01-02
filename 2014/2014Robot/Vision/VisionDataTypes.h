/*
 * VisionDataTypes.h
 *
 *  Created on: Mar 9, 2014
 *      Author: nowireless
 */

#ifndef VISIONDATATYPES_H_
#define VISIONDATATYPES_H_

struct ParticleStageOneScoreReport {
	float aspectRatioVerticalScore;
	float aspectRatioHorizontalScore;
	float rectangularityScore;
};

struct ParticleStageTwoScoreReport {
	int particleVertical;
	int particleHorizontal;
	float totalScore;
	float leftScore;
	float rightScore;
	float tapeWidthScore;
	float verticalScore;
};

enum TargetID {
	kNoTarget,
	kVertical,
	kHorizontal
};

enum HotSide {
	kNoHotSide,
	kLeft,
	kRight
};

struct ParticleIDReport {
	TargetID targetID;
	int particleNumber;
};

#endif /* VISIONDATATYPES_H_ */
