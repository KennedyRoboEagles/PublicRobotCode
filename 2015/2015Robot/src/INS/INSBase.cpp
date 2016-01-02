//
//  INSBase.cpp
//  INSTest
//
//  Created by Ryan Sjostrand on 2/8/15.
//  Copyright (c) 2015 Ryan Sjostrand. All rights reserved.
//

#include "INSBase.h"
#include <cmath>


/*
 * Update Interval in seconds
 */
INSBase::INSBase(double updateInterval) {
    this->updateInterval = updateInterval;
    this->Reset();
}

void INSBase::Reset() {
    this->xVelocity = 0;
    this->yVelocity = 0;
    this->x = 0;
    this->y = 0;
    this->isMoving = true;
}

void INSBase::SetIsMoving(bool moving) {
    this->isMoving = moving;
}

void INSBase::SetXAccelThreshold(double threshold) {
    this->xAccelThreshold = threshold;
}
void INSBase::SetYAccelThreshold(double threshold) {
    this->yAccelThreshold = threshold;
}

bool INSBase::IsMoving() { return this->isMoving; }
double INSBase::GetVelocityX() { return this->xVelocity; }
double INSBase::GetVelocityY() { return this->yVelocity; }
double INSBase::GetPositionX() { return this->x; }
double INSBase::GetPositionY() { return this->y; }

void INSBase::Update(double xAccel, double yAccel) {
    double xAcceleration = xAccel;
    double yAcceleration = yAccel;
    
    if (fabs(xAccel) < xAccelThreshold) {
        xAcceleration = 0.0;
    }
    
    if (fabs(yAccel) < yAccelThreshold) {
        yAcceleration = 0.0;
    }
    
    if(!this->IsMoving()) {
        this->xVelocity = 0.0;
        this->yVelocity = 0.0;
    } else {
        this->xVelocity += xAcceleration * updateInterval;
        this->yVelocity += yAcceleration * updateInterval;
    }
    
    
    this->x += xVelocity * updateInterval;
    this->y += yVelocity * updateInterval;

    printf("[InsBase] xAccel %f, yAccel %f, xVel %f, yVel %f, x %f, y %f\n", xAcceleration, yAcceleration, this->xVelocity, this->yVelocity, this->x, this->y);
}
