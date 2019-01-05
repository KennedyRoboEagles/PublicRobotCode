/*
 * SRXWrapper.h
 *
 *  Created on: Jan 19, 2018
 *      Author: nowir
 */

#ifndef SRC_UTIL_SRXWRAPPER_H_
#define SRC_UTIL_SRXWRAPPER_H_

#include <SmartDashboard/SendableBase.h>
#include <SpeedController.h>

#include <ctre/Phoenix.h>

class SRXWrapper: public frc::SpeedController, public frc::SendableBase {
public:
	class EncoderWrapper: public frc::SendableBase {
	public:
		EncoderWrapper(TalonSRX *talon) {
			talon_ = talon;
			SetName("Encoder", talon_->GetDeviceID());
		}

	protected:
		virtual void InitSendable(frc::SendableBuilder& builder) override {
			builder.SetSmartDashboardType("Quadrature Encoder");
			builder.AddDoubleProperty("Speed", [=]() { return talon_->GetSelectedSensorVelocity(0); }, nullptr);
		    builder.AddDoubleProperty("Distance", [=]() { return talon_->GetSelectedSensorPosition(0); }, nullptr);
		    builder.AddDoubleProperty("Distance per Tick", [=]() { return 0; }, nullptr);
		}
	private:
		TalonSRX *talon_;
	};

	enum Mode {
		kPercentVelocity,
		kPercentVoltage
	};


	SRXWrapper(TalonSRX* talon, Mode mode, double maxSpeed);
	virtual ~SRXWrapper() {}

	void SetMode(Mode mode);
	Mode GetMode();

	void Set(double speed) override;
	double Get() const override;

	void SetInverted(bool isInverted) override;
	bool GetInverted() const override;

	void Disable() override;
	void StopMotor() override;

	void PIDWrite(double output) override;
protected:
	virtual void InitSendable(frc::SendableBuilder& builder);
private:
	TalonSRX *talon_;
	EncoderWrapper* encoder_;
	Mode mode_;
	double maxSpeed_;
};

#endif /* SRC_UTIL_SRXWRAPPER_H_ */
