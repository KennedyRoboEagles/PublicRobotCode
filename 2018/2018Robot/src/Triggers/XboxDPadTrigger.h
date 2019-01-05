/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <Buttons/Trigger.h>
#include <XboxController.h>

class XboxDPadTrigger : public frc::Trigger {
public:
	XboxDPadTrigger(frc::XboxController* x, int angle);
	bool Get() override;
private:
	frc::XboxController* x_;
	int angle_;
};

