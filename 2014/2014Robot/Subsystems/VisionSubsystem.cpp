#include "VisionSubsystem.h"
#include "../Robotmap.h"
#include "../Vision/ImageProcessing.h"
#include "../Vision/ParticleAnalysis.h"
#include "../Vision/ParticleScoring.h"
#include "../Vision/ParticleIdentification.h"

VisionSubsystem::VisionSubsystem() : Subsystem("VisionSubsystem") {
	this->isHotTargetPresenet = false;
}
    
void VisionSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}


// Put methods for controlling this subsystem
// here. Call these from Commands.
void VisionSubsystem::DetectHotGoal() {
	ImageProcessing *imgProcTest = new ImageProcessing();
	imgProcTest->SetThreshold(105, 137, 230, 255, 133, 183);
	//if(!imgProcTest->ProcessCameraImage()) {
	//	printf("[VisionSubsystem] Axis camera image biffer is null ending\n");
		delete imgProcTest;
		return;
	//}
	
	vector<ParticleAnalysisReport> *reports = imgProcTest->GetParticleReports();
	if(reports == NULL || reports->size() == 0) {
		printf("[VisionSubsystem] There are no particle reports to use ending\n");
		delete imgProcTest;
	}
	
	ParticleScoring *scoringTest = new ParticleScoring();
	scoringTest->StageOneScoring(imgProcTest->GetFilteredImage(), imgProcTest->GetParticleReports());
	ParticleIdentification *particleID = new ParticleIdentification();
	particleID->IDParticles(scoringTest->GetParticleStageOneScores());

	scoringTest->StageTwoScoring(
			imgProcTest->GetFilteredImage(),
			imgProcTest->GetParticleReports(),
			particleID->GetVerticalIDReports(),
			particleID->GetHorizontalIDReports()
			);

	ParticleAnalysis *particleAnalysis = new ParticleAnalysis();

	particleAnalysis->DetectHotSide(scoringTest->GetBestStageTwoScore());
	this->isHotTargetPresenet = particleAnalysis->IsHotTargetVisable();
	if(particleAnalysis->IsHotTargetVisable()) {
		printf("Hot Target Visible\n");
	} else {
		printf("Hot Target Not visible\n");
	}
	switch (particleAnalysis->GetHotSide()) {
	case kNoHotSide:
		printf("No Hot Side\n");
		break;
	case kLeft:
		printf("Hotside: Left\n");
		break;
	case kRight:
		printf("HotSide: Right\n");
		break;
	default:
		printf("Unknown\n");
		break;
	}
	delete particleAnalysis;
	delete particleID;
	delete scoringTest;
	delete imgProcTest;
}
bool VisionSubsystem::IsHotTargetPressent() {
	return this->isHotTargetPresenet;
}

void VisionSubsystem::WriteCameraImage() {
	AxisCamera &camera = AxisCamera::GetInstance("10.30.81.11");
	RGBImage *image = new RGBImage();
	int error = camera.GetImage(image);
	if(error == 0) {
		printf("[VisionSubsystem] Axis image buffer is null ending\n");
		delete image;
		return;
	}
	image->Write("/cameraImage.bmp");
	delete image;
}

void VisionSubsystem::Reset() {
	this->isHotTargetPresenet = false;
}
