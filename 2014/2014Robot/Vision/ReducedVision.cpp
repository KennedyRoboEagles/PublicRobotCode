/*
 * ReducedVision.cpp
 *
 *  Created on: Mar 27, 2014
 *      Author: nowireless
 */

#include "ReducedVision.h"
#include "ImageProcessing.h"
#include "ParticleScoring.h"
#include "ParticleIdentification.h"

ReducedVision::ReducedVision() {
	// TODO Auto-generated constructor stub

}

ReducedVision::~ReducedVision() {
	// TODO Auto-generated destructor stub
}

bool ReducedVision::HotTargetVisable(ColorImage *image) {
	//First Pass
	ImageProcessing *imgProcTest = new ImageProcessing();
	imgProcTest->SetThreshold(105, 137, 230, 255, 133, 183);

	imgProcTest->Process(image);


	//Second Pass
	ParticleScoring *scoringTest = new ParticleScoring();
	scoringTest->StageOneScoring(imgProcTest->GetFilteredImage(), imgProcTest->GetParticleReports());


	//Third Pass
	ParticleIdentification *particleID = new ParticleIdentification();
	particleID->IDParticles(scoringTest->GetParticleStageOneScores());

	bool isHot = particleID->GetHorizontalIDReports()->size() >= 1;
	delete particleID;
	delete scoringTest;
	delete imgProcTest;
	return isHot;
}
