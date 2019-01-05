/*
 * DummyPIDOutput.h
 *
 *  Created on: Mar 12, 2018
 *      Author: nowir
 */

#ifndef SRC_UTIL_NULLPIDOUTPUT_H_
#define SRC_UTIL_NULLPIDOUTPUT_H_

#include <PIDOutput.h>

class NullPIDOutput : public frc::PIDOutput {
public:
	NullPIDOutput();
	virtual ~NullPIDOutput();
	void PIDWrite(double value) override {}
};

#endif /* SRC_UTIL_NULLPIDOUTPUT_H_ */
