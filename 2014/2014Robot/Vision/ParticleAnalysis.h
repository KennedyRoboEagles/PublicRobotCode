/*
 * ParticleAnalysis.h
 *
 *  Created on: Mar 10, 2014
 *      Author: nowireless
 */

#ifndef PARTICLEANALYSIS_H_
#define PARTICLEANALYSIS_H_

#include "VisionConfig.h"
#include "VisionDataTypes.h"

class ParticleAnalysis {
private:
	HotSide m_hotSide;
	bool m_hotTargetVisable;
public:
	ParticleAnalysis();
	virtual ~ParticleAnalysis();
	void DetectHotSide(ParticleStageTwoScoreReport *report);
	HotSide GetHotSide();
	bool IsHotTargetVisable();
};

#endif /* PARTICLEANALYSIS_H_ */
