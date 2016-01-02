/*
 * INS.h
 *
 *  Created on: Feb 22, 2015
 *      Author: nowireless
 */

#ifndef SRC_INS_INS_H_
#define SRC_INS_INS_H_

#include <INS/INSBase.h>
//#include <Sensors/UsbMouseMovement.h>

static const double kINSUpdateFrequency = 0.02; //50 mS

class INS {
public:
	static INS* GetInstance();

	INS();
	INSBase *GetINSBase();
	//UsbMouseMovement *GetMouse();

	double GetPositionX();
	double GetPositionY();
	double GetVelocityX();
	double GetVelocityY();

	void SetXAccelThreshold(double threshold);
	void SetYAccelThreshold(double threshold);
	void SetIsMoving(bool moving);
	bool IsMoving();

	void Update(double xAccel, double yAccel);

	void Enable();
	void Disable();
	bool IsEnabled();
	void Reset();

private:
	static INS *instnace;
	INSBase *ins;
	bool enabled;

	//UsbMouseMovement *mouse;
};

#endif /* SRC_INS_INS_H_ */
