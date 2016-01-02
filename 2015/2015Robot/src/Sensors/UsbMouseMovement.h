/*
 * UsbMouse.h
 *
 *  Created on: Mar 12, 2015
 *      Author: nowireless
 */

#ifndef SRC_SENSORS_USBMOUSE_H_
#define SRC_SENSORS_USBMOUSE_H_

#include <linux/input.h>
#include <thread>

class UsbMouseMovement {
private:
	int fd;
	input_event ie;
	std::thread *updateThread;
	bool running;
	bool enabled;

	double lastCheckIn;

	void Init();
	void Update();

public:
	UsbMouseMovement();
	virtual ~UsbMouseMovement();

	static void Run(UsbMouseMovement *instance);

	void SetEnabled(bool enabled);
	bool IsEnabled();

	void SetRunning(bool run);
	bool IsRunning();

	bool IsMouseOpen();

	bool IsMoving();
};

#endif /* SRC_SENSORS_USBMOUSE_H_ */
