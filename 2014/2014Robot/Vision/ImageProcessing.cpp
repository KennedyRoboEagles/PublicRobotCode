/*
 * ImageProcessing.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: nowireless
 */

#include "ImageProcessing.h"
#include "VisionConfig.h"
#include <nivision.h>

ImageProcessing::ImageProcessing() {
	this->m_filteredImage = NULL;
	this->m_image = NULL;
	this->m_hMin = 0;
	this->m_hMax = 255;
	this->m_sMin = 0;
	this->m_sMax = 255;
	this->m_vMin = 0;
	this->m_vMax = 255;
}

ImageProcessing::~ImageProcessing() {
	if(this->m_filteredImage != NULL) {
		delete this->m_filteredImage;
	}
	if(this->m_image != NULL) {
		delete this->m_image;
	}
}

bool ImageProcessing::ProcessCameraImage() {
	AxisCamera &camrera = AxisCamera::GetInstance("10.30.81.11");
	this->m_image = new RGBImage();
	int error = camrera.GetImage(m_image);
	if(error == 0 ) {
		return false;
	}
	this->process(this->m_image, NULL,NULL);
	return true;
}
void ImageProcessing::ProcessFilesystemImage(const char *path, const char *pathThresholded, const char *pathFiltered) {
	printf("[ImageProcessing] Going to process Image %s\n", path);
	this->m_image = new RGBImage(path);
	printf("[ImageProcessing] Image Size %i by %i\n", m_image->GetWidth(), m_image->GetHeight());
	this->process(this->m_image,pathThresholded,pathFiltered);
	printf("[ImageProcessing] Particles %i\n", this->m_filteredImage->GetOrderedParticleAnalysisReports()->size());
}
void ImageProcessing::SaveCameraImage() {
	AxisCamera &camera = AxisCamera::GetInstance("10.30.81.11");
	camera.GetImage()->Write("/CameraImage.bmp");
}
void ImageProcessing::SetThreshold(int hMin, int hMax, int sMin, int sMax, int vMin, int vMax) {
	this->m_hMin = hMin;
	this->m_hMax = hMax;
	this->m_sMin = sMin;
	this->m_sMax = sMax;
	this->m_vMin = vMin;
	this->m_vMax = vMax;

}
vector<ParticleAnalysisReport> *ImageProcessing::GetParticleReports() {
	if(this->m_filteredImage != NULL) {
		return this->m_filteredImage->GetOrderedParticleAnalysisReports();
	}
	return NULL;
}

BinaryImage *ImageProcessing::GetFilteredImage() {
	return this->m_filteredImage;
}

void ImageProcessing::process(ColorImage *image, const char *pathThresholded, const char *pathFiltered) {
	BinaryImage *thresholdImage = image->ThresholdHSV(m_hMin,m_hMax, m_sMin, m_sMax, m_vMin, m_vMax);
	BinaryImage *closedImage = BasicMorphologyClose(thresholdImage);
	BinaryImage *filledImage = AdvancedMorphologyFill(closedImage);
	BinaryImage *convexHulledImage = filledImage->ConvexHull(false);
	ParticleFilterCriteria2 criteria[] = { {IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}};
	BinaryImage *filteredImage = convexHulledImage->ParticleFilter(criteria, 1);

	if(DEBUG_WRITE_IMAGE) {
		if(pathFiltered != NULL && pathThresholded != NULL) {
			thresholdImage->Write(pathThresholded);
			filteredImage->Write(pathFiltered);
		}
	}

	this->m_filteredImage = filteredImage;
	delete convexHulledImage;
	delete filledImage;
	delete closedImage;
	delete thresholdImage;

}

BinaryImage *ImageProcessing::BasicMorphologyClose(BinaryImage *image) {
	int pKernel[9] = {1,0,1,0,1,0,1,0,1};

	StructuringElement structElem;
	structElem.matrixCols = 3;
	structElem.matrixRows = 3;
	structElem.hexa = FALSE;
	structElem.kernel = pKernel;

	BinaryImage *destImage = new BinaryImage();

	imaqMorphology(destImage->GetImaqImage(), image->GetImaqImage(), IMAQ_CLOSE, &structElem);

	return destImage;
}
BinaryImage *ImageProcessing::AdvancedMorphologyFill(BinaryImage *image) {
	BinaryImage *destImage = new BinaryImage();
	imaqFillHoles(destImage->GetImaqImage(),image->GetImaqImage(), true);
	return destImage;
}

void ImageProcessing::Process(ColorImage *image) {
	this->process(image, NULL,NULL);
}
