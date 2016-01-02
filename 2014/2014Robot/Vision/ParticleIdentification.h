/*
 * ParticleIdentification.h
 *
 *  Created on: Mar 9, 2014
 *      Author: nowireless
 */

#ifndef PARTICLEIDENTIFICATION_H_
#define PARTICLEIDENTIFICATION_H_

#include <vector>
#include "VisionDataTypes.h"

using namespace std;
class ParticleIdentification {
private:
	vector<ParticleIDReport> *m_particleIDReports;
	vector<ParticleIDReport> *m_particleIDHorizontalReports;
	vector<ParticleIDReport> *m_particleIDVerticalReports;
	TargetID compareScores(ParticleStageOneScoreReport report, int i);
	char* TargetIDToChar(TargetID id);
public:

	ParticleIdentification();
	virtual ~ParticleIdentification();
	void IDParticles(vector<ParticleStageOneScoreReport> *scoreReports);
	vector<ParticleIDReport> *GetParticleIDReports();
	vector<ParticleIDReport> *GetHorizontalIDReports();
	vector<ParticleIDReport> *GetVerticalIDReports();
};

#endif /* PARTICLEIDENTIFICATION_H_ */
