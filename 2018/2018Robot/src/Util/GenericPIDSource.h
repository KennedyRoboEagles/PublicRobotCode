/*
 * GenericPIDSource.h
 *
 *  Created on: Mar 17, 2018
 *      Author: nowir
 */

#ifndef SRC_UTIL_GENERICPIDSOURCE_H_
#define SRC_UTIL_GENERICPIDSOURCE_H_

#include <PIDSource.h>

class GenericPIDSource : public frc::PIDSource {
public:
	GenericPIDSource();
	virtual ~GenericPIDSource();
	void Set(double value);

	double PIDGet() override;
private:
	double value_;
};


#endif /* SRC_UTIL_GENERICPIDSOURCE_H_ */
