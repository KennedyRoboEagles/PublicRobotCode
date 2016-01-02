/*
 * ParticleIdentification.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: nowireless
 */

#include "ParticleIdentification.h"
#include "VisionConfig.h"
#include <nivision.h>

ParticleIdentification::ParticleIdentification() {
	this->m_particleIDReports = NULL;
	this->m_particleIDHorizontalReports = NULL;
	this->m_particleIDVerticalReports = NULL;

}

ParticleIdentification::~ParticleIdentification() {
	if(this->m_particleIDReports != NULL) {
		delete this->m_particleIDReports;
	}
	if(this->m_particleIDHorizontalReports != NULL) {
		delete this->m_particleIDHorizontalReports;
	}
	if(this->m_particleIDVerticalReports != NULL) {
		delete this->m_particleIDVerticalReports;
	}
}

void ParticleIdentification::IDParticles(vector<ParticleStageOneScoreReport> *scoreReports) {
	if(scoreReports == NULL || scoreReports->size() == 0) {
		return;
	}
	m_particleIDReports = new vector<ParticleIDReport>;
	m_particleIDHorizontalReports = new vector<ParticleIDReport>;
	m_particleIDVerticalReports = new vector<ParticleIDReport>;
	printf("[ParticleIdentification] Starting IDing\n");
	printf("[ParticleIdentification] Score Report Size %i\n", scoreReports->size());
	for (int i = 0; i < scoreReports->size(); i++) {
		ParticleIDReport idReport;
		idReport.particleNumber = i;

		idReport.targetID = compareScores(scoreReports->at(i), i);

		//printf("[ParticleIdentification] Particle: %i is a %s", TargetIDToChar(idReport.targetID));
		//printf("[ParticleIdentification] Particle: %i is a %s", TargetIDToChar(kNoTarget));
		m_particleIDReports->push_back(idReport);

		switch (idReport.targetID) {
			case kHorizontal:
				m_particleIDHorizontalReports->push_back(idReport);
				break;
			case kVertical:
				m_particleIDVerticalReports->push_back(idReport);
				break;
			default:
				break;
		}
	}
}

TargetID ParticleIdentification::compareScores(ParticleStageOneScoreReport report, int i) {
	bool validTarget = true;

	validTarget &= report.rectangularityScore > SCORING_RECTANGULARITY_LIMIT;
	if(report.aspectRatioVerticalScore > SCORING_ASPECT_RATIO_LIMIT) {
		printf("[ParticleIdentification] Particle: %i is a Vertical Target\n", i);
		return kVertical;
	} else if(report.aspectRatioHorizontalScore > SCORING_ASPECT_RATIO_LIMIT) {
		printf("[ParticleIdentification] Particle: %i is a Horizontal Target\n", i);
		return kHorizontal;
	} else {
		printf("[ParticleIdentification] Particle: %i is a not an Target\n", i);
		return kNoTarget;
	}
}

char* ParticleIdentification::TargetIDToChar(TargetID id) {
	char *msg;
	switch (id) {
	case kVertical:
		msg = "Vertical";
		break;
	case kHorizontal:
		msg = "Horizontal";
		break;
	case kNoTarget:
		msg = "Not an";
		break;
	default:
		msg =  "Unknown";
	}
	return msg;
}

vector<ParticleIDReport> *ParticleIdentification::GetParticleIDReports() {
	return this->m_particleIDReports;
}


vector<ParticleIDReport> *ParticleIdentification::GetHorizontalIDReports() {
	return this->m_particleIDHorizontalReports;
}

vector<ParticleIDReport> *ParticleIdentification::GetVerticalIDReports() {
	return this->m_particleIDVerticalReports;
}
