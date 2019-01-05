/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "XboxDPadTrigger.h"

XboxDPadTrigger::XboxDPadTrigger(frc::XboxController* x, int angle) {
	x_ = x;
	angle_ = angle;
}

bool XboxDPadTrigger::Get() {
	return x_->GetPOV(0) == angle_;
}

