/*
 * SRXWrapper.cpp
 *
 *  Created on: Jan 19, 2018
 *      Author: nowir
 */

#include "SRXWrapper.h"
#include <ctre/Phoenix.h>

SRXWrapper::SRXWrapper(TalonSRX* talon, Mode mode, double maxSpeed) {
	talon_ = talon;
	mode_ = mode;
	maxSpeed_ = maxSpeed;
	SetName("Talon SRX ", talon_->GetDeviceID());

	encoder_ = new EncoderWrapper(talon);
	this->AddChild(encoder_);
}

void SRXWrapper::SetMode(Mode mode) {
	mode_ = mode;
}

SRXWrapper::Mode SRXWrapper::GetMode() {
	return mode_;
}

void SRXWrapper::Set(double speed) {
	switch(mode_) {
		case kPercentVoltage:
		talon_->Set(ControlMode::PercentOutput, speed);
		break;
		case kPercentVelocity:
		talon_->Set(ControlMode::Velocity, speed * maxSpeed_);
		break;
		default:
		talon_->Set(ControlMode::PercentOutput, 0);
		break;
	}
}

double SRXWrapper::Get() const {
	return talon_->GetMotorOutputPercent();
}

void SRXWrapper::SetInverted(bool isInverted) {
	talon_->SetInverted(isInverted);
}

bool SRXWrapper::GetInverted() const {
	return talon_->GetInverted();
}

void SRXWrapper::Disable() {
	talon_->NeutralOutput();
}

void SRXWrapper::StopMotor() {
	talon_->NeutralOutput();
}

void SRXWrapper::PIDWrite(double output) {
	this->Set(output);
}


void SRXWrapper::InitSendable(frc::SendableBuilder& builder) {
	builder.SetSmartDashboardType("Speed Controller");
	builder.SetSafeState([=]() {StopMotor();});
	builder.AddDoubleProperty("Value", [=]() {return Get();},
			[=](double value) {Set(value);});
}
