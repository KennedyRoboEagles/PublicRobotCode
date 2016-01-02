/*
 * ImageProcessing.h
 *
 *  Created on: Feb 27, 2014
 *      Author: nowireless
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_

#include <Vision/RGBImage.h>
#include <Vision/ColorImage.h>
#include <Vision/BinaryImage.h>
#include <Vision/AxisCamera.h>

class ImageProcessing {
private:
	BinaryImage *m_filteredImage;
	ColorImage *m_image;
	BinaryImage *BasicMorphologyClose(BinaryImage *image);
	BinaryImage *AdvancedMorphologyFill(BinaryImage *image);
	//Threshold *m_threshold;
	int m_hMin;
	int m_hMax;
	int m_sMin;
	int m_sMax;
	int m_vMin;
	int m_vMax;
	void process(ColorImage *image, const char *pathThresholded, const char *pathFiltered);
public:
	ImageProcessing();
	bool ProcessCameraImage();
	void ProcessFilesystemImage(const char *path,const char *pathThresholded, const char *pathFiltered);
	void Process(ColorImage *image);
	void SaveCameraImage();
	void SetThreshold(int hMin, int hMax, int sMin, int sMax, int vMin, int vMax);
	vector<ParticleAnalysisReport> *GetParticleReports();
	BinaryImage *GetFilteredImage();
	virtual ~ImageProcessing();

};

#endif /* IMAGEPROCESSING_H_ */
