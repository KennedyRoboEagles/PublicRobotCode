/*
 * ParticleAnalysis.cpp
 *
 *  Created on: Mar 10, 2014
 *      Author: nowireless
 */

#include "ParticleAnalysis.h"

ParticleAnalysis::ParticleAnalysis() {
	// TODO Auto-generated constructor stub
	this->m_hotSide = kNoHotSide;
	this->m_hotTargetVisable = false;

}

ParticleAnalysis::~ParticleAnalysis() {
	// TODO Auto-generated destructor stub
}

void ParticleAnalysis::DetectHotSide(ParticleStageTwoScoreReport *report) {
	bool isHot = true;

	isHot &= report->tapeWidthScore >= ANALYSIS_TAPE_WIDTH_LIMIT;
	isHot &= report->verticalScore >= ANALYSIS_VERTICAL_SCORE_LIMIT;

	if(isHot) {
		if(report->leftScore > ANALYSIS_LR_SCORE_LIMIT) {
			m_hotSide = kLeft;
		} else if(report->rightScore > ANALYSIS_LR_SCORE_LIMIT) {
			m_hotSide = kRight;
		} else {
			m_hotSide = kNoHotSide;
		}
	}
	isHot &= (report->leftScore > ANALYSIS_LR_SCORE_LIMIT) | (report->rightScore > ANALYSIS_LR_SCORE_LIMIT);
	this->m_hotTargetVisable = isHot;
}

HotSide ParticleAnalysis::GetHotSide() {
	return this->m_hotSide;
}

bool ParticleAnalysis::IsHotTargetVisable() {
	return this->m_hotTargetVisable;
}
