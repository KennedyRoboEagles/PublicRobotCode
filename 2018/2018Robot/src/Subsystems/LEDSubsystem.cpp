/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "LEDSubsystem.h"
#include "../RobotMap.h"
#include "Commands/LEDCommand.h"

LEDSubsystem::LEDSubsystem() : Subsystem("ExampleSubsystem") {
//	canifier_ = new CANifier(kCANIfierID);
	SetRGB(0, 0, 0);
}

void LEDSubsystem::InitDefaultCommand() {
	// Set the default command for a subsystem here.
	// SetDefaultCommand(new MySpecialCommand());
	SetDefaultCommand(new LEDCommand());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.
void LEDSubsystem::SetRGB(double r, double g, double b) {
//	canifier_->SetLEDOutput(r, CANifier::LEDChannel::LEDChannelA);
//	canifier_->SetLEDOutput(g, CANifier::LEDChannel::LEDChannelB);
//	canifier_->SetLEDOutput(b, CANifier::LEDChannel::LEDChannelC);

}
