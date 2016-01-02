/*
 * ParticleScoring.h
 *
 *  Created on: Mar 9, 2014
 *      Author: nowireless
 */

#ifndef PARTICLESCORING_H_
#define PARTICLESCORING_H_

#include <Vision/BinaryImage.h>
#include "VisionDataTypes.h"

class ParticleScoring {
private:
	/*
	 * Stage One
	 */
	vector<ParticleStageOneScoreReport> *m_particleScores;
	float scoreRectangularity(ParticleAnalysisReport *report);
	float scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, TargetID target);

	/*
	 * Stage Two
	 */
	vector<ParticleStageTwoScoreReport> *m_stageTwoScores;
	ParticleStageTwoScoreReport m_bestStageTwoScore;

	float ratioToScore(float ratio);

public:
	ParticleScoring();
	virtual ~ParticleScoring();
	void StageOneScoring(BinaryImage *image, vector<ParticleAnalysisReport> *reports);
	vector<ParticleStageOneScoreReport> *GetParticleStageOneScores();
	void StageTwoScoring(BinaryImage *image, vector<ParticleAnalysisReport> *reports, vector<ParticleIDReport> *verticalIDReports, vector<ParticleIDReport> *horizontalIDReports);
	ParticleStageTwoScoreReport *GetBestStageTwoScore();
	vector<ParticleStageTwoScoreReport> *GetStageTwoScoreReports();
};

#endif /* PARTICLESCORING_H_ */
