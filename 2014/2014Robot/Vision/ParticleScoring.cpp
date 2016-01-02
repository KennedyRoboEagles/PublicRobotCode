/*
 * ParticleScoring.cpp
 *
 *  Created on: Mar 9, 2014
 *      Author: nowireless
 */

#include "ParticleScoring.h"
#include "VisionConfig.h"
#include <cmath>

ParticleScoring::ParticleScoring() {
	// TODO Auto-generated constructor stub
	this->m_particleScores = NULL;
	this->m_stageTwoScores = NULL;
	this->m_bestStageTwoScore.leftScore = 0;
	this->m_bestStageTwoScore.particleHorizontal = 0;
	this->m_bestStageTwoScore.particleVertical = 0;
	this->m_bestStageTwoScore.rightScore = 0;
	this->m_bestStageTwoScore.tapeWidthScore = 0;
	this->m_bestStageTwoScore.totalScore = 0;
	this->m_bestStageTwoScore.verticalScore = 0;
}

ParticleScoring::~ParticleScoring() {
	// TODO Auto-generated destructor stub
	if(this->m_particleScores != NULL) {
		delete m_particleScores;
	}
	if(this->m_stageTwoScores != NULL) {
		delete m_stageTwoScores;
	}
}

void ParticleScoring::StageOneScoring(BinaryImage *image, vector<ParticleAnalysisReport> *reports) {
	printf("[ParticleScoring] Starting Stage One\n");
	printf("[ParticleScoring] Reports Size %i \n", reports->size());
	if(reports == NULL || reports->size() == 0) {
		return;
	}

	this->m_particleScores = new vector<ParticleStageOneScoreReport>;
	for(unsigned int i = 0; (i < SCORE_MAXPARTICLES) && (i < reports->size()); i++) {
		ParticleAnalysisReport *report = &(reports->at(i));
		ParticleStageOneScoreReport scores;

		scores.rectangularityScore			= scoreRectangularity(report);
		scores.aspectRatioHorizontalScore	= scoreAspectRatio(image, report, kHorizontal);
		scores.aspectRatioVerticalScore		= scoreAspectRatio(image, report, kVertical);

		printf("[ParticleScoring] Particle:%i Scores- Rect: %f, AspectHorizontal: %f, AspectVertical: %f\n", i, scores.rectangularityScore, scores.aspectRatioHorizontalScore, scores.aspectRatioVerticalScore);

		m_particleScores->push_back(scores);
	}
}

float ParticleScoring::scoreRectangularity(ParticleAnalysisReport *report) {
	if (report->boundingRect.width * report->boundingRect.height != 0) {
		return 100 * report->particleArea / (report->boundingRect.width * report->boundingRect.height);
	} else {
		return 0;
	}
}

float ParticleScoring::scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, TargetID target) {
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	switch (target) {
		case kVertical:
			idealAspectRatio = (TARGET_VERTICAL_WIDTH / TARGET_VERTICAL_HEIGHT);
			break;
		case kHorizontal:
			idealAspectRatio = (TARGET_HORIZONTAL_WIDTH / TARGET_HORIZONTAL_HEIGHT);
			break;
		default:
			return 0;
			break;
	}

	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);

	//Divide width by height to measure aspect ratio
	if (report->boundingRect.width > report->boundingRect.height) {
		//particle is wider than it is tall, divide long by short
		aspectRatio = ratioToScore(((rectLong / rectShort) / idealAspectRatio));
	} else {
		//particle is taller than it is wide, divide short by long
		aspectRatio = ratioToScore(((rectShort / rectLong) / idealAspectRatio));
	}
	return aspectRatio;		//force to be in range 0-100
}

float ParticleScoring::ratioToScore(float ratio) {
	double min1 = 100*(1.0-fabs(1-ratio));
	double min2 = 100;
	return (max(0.0, min(min1, min2)));
}

vector<ParticleStageOneScoreReport> *ParticleScoring::GetParticleStageOneScores() {
	return this->m_particleScores;
}

void ParticleScoring::StageTwoScoring(BinaryImage *image, vector<ParticleAnalysisReport> *reports, vector<ParticleIDReport> *verticalIDReports, vector<ParticleIDReport> *horizontalIDReports) {
	if(image == NULL || verticalIDReports == NULL || horizontalIDReports == NULL || verticalIDReports->size() == 0 || horizontalIDReports->size() == 0) {
		return;
	}

	m_bestStageTwoScore.totalScore = m_bestStageTwoScore.leftScore = m_bestStageTwoScore.rightScore = m_bestStageTwoScore.tapeWidthScore = m_bestStageTwoScore.verticalScore = 0;

	m_stageTwoScores = new vector<ParticleStageTwoScoreReport>;

	for(unsigned int i = 0; i < verticalIDReports->size(); i++) {
		ParticleAnalysisReport *verticalTargetReport = &(reports->at(verticalIDReports->at(i).particleNumber));
		for(unsigned int j = 0; j < horizontalIDReports->size(); j++) {
			ParticleAnalysisReport *horizontalTargetReport = &(reports->at(horizontalIDReports->at(j).particleNumber));
			ParticleStageTwoScoreReport scores;
			scores.leftScore = 0;
			scores.particleHorizontal = 0;
			scores.particleVertical = 0;
			scores.rightScore = 0;
			scores.tapeWidthScore = 0;
			scores.totalScore = 0;
			scores.verticalScore = 0;

			double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;

			//Measure equivalent rectangle sides for use in score calculation
			imaqMeasureParticle(image->GetImaqImage(), horizontalTargetReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
			imaqMeasureParticle(image->GetImaqImage(), verticalTargetReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
			imaqMeasureParticle(image->GetImaqImage(), horizontalTargetReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);

			//Determine if the horizontal target is in the expected location to the left of the vertical target
			leftScore = ratioToScore(1.2*(verticalTargetReport->boundingRect.left - horizontalTargetReport->center_mass_x)/horizWidth);
			printf("[ParticleScoring] Left Score:%f, Ratio:%f\n",leftScore,(1.2*(verticalTargetReport->boundingRect.left - horizontalTargetReport->center_mass_x)/horizWidth));
			//Determine if the horizontal target is in the expected location to the right of the  vertical target
			rightScore = ratioToScore(1.2*(horizontalTargetReport->center_mass_x - verticalTargetReport->boundingRect.left - verticalTargetReport->boundingRect.width)/horizWidth);
			printf("[ParticleScoring] Right Score:%f, Ratio:%f\n", rightScore, (1.2*(horizontalTargetReport->center_mass_x - verticalTargetReport->boundingRect.left - verticalTargetReport->boundingRect.width)/horizWidth));
			//Determine if the width of the tape on the two targets appears to be the same
			tapeWidthScore = ratioToScore(vertWidth/horizHeight);
			//Determine if the vertical location of the horizontal target appears to be correct
			verticalScore = ratioToScore(1-(verticalTargetReport->boundingRect.top - horizontalTargetReport->center_mass_y)/(4*horizHeight));
			total = leftScore > rightScore ? leftScore:rightScore;
			total += tapeWidthScore + verticalScore;

			scores.leftScore = leftScore;
			scores.rightScore = rightScore;
			scores.tapeWidthScore = tapeWidthScore;
			scores.verticalScore = verticalScore;
			scores.particleHorizontal = j;
			scores.particleVertical = i;

			printf("[ParticleScoring] Particles V: %i H:%i Scores- Tape: %f, Left: %f, Right: %f, Vertical: %f, Total: %f\n",
					scores.particleVertical,
					scores.particleHorizontal,
					scores.tapeWidthScore,
					scores.leftScore,
					scores.rightScore,
					scores.verticalScore,
					scores.totalScore
					);

			if(scores.totalScore >= m_bestStageTwoScore.totalScore) {
				m_bestStageTwoScore = scores;
			}
			m_stageTwoScores->push_back(scores);
		}
		printf("[ParticleScoring] Best Target Score, Particles V: %i H:%i Scores- Tape: %f, Left: %f, Right: %f, Vertical: %f, Total: %f\n",
				m_bestStageTwoScore.particleVertical,
				m_bestStageTwoScore.particleHorizontal,
				m_bestStageTwoScore.tapeWidthScore,
				m_bestStageTwoScore.leftScore,
				m_bestStageTwoScore.rightScore,
				m_bestStageTwoScore.verticalScore,
				m_bestStageTwoScore.totalScore
				);
	}
}
ParticleStageTwoScoreReport *ParticleScoring::GetBestStageTwoScore() {
	return &this->m_bestStageTwoScore;
}
vector<ParticleStageTwoScoreReport> *ParticleScoring::GetStageTwoScoreReports() {
	return this->m_stageTwoScores;
}
