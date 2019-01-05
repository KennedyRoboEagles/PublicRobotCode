#ifndef DriveRateCommand_H
#define DriveRateCommand_H

#include <PIDController.h>
#include <PIDOutput.h>
#include <PIDSource.h>
#include <atomic>

#include "CommandBase.h"

class FieldOrientedDriveCommand : public CommandBase, PIDOutput, PIDSource {
private:
	frc::PIDController* rateController_;
	std::atomic<double> turnComp_;
public:
	FieldOrientedDriveCommand();
	void Initialize();
	void Execute();
	bool IsFinished();
	void End();
	void Interrupted();

	void PIDWrite(double output) override;
	double PIDGet() override;
};

#endif  // DriveRateCommand_H
