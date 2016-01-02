//
//  INSBase.h
//  INSTest
//
//  Created by Ryan Sjostrand on 2/8/15.
//  Copyright (c) 2015 Ryan Sjostrand. All rights reserved.
//

#ifndef __INSTest__INSBase__
#define __INSTest__INSBase__

#include <stdio.h>

class INSBase {
private:
    double updateInterval;
    bool isMoving;
    
    double xAccelThreshold;
    double yAccelThreshold;
    
    double xVelocity;
    double yVelocity;
    double x;
    double y;
public:
    INSBase(double updateInterval);
    bool IsMoving();
    void SetIsMoving(bool moving);
    
    void SetXAccelThreshold(double threshold);
    void SetYAccelThreshold(double threshold);
    
    double GetVelocityX();
    double GetVelocityY();
    double GetPositionX();
    double GetPositionY();
    
    void Reset();
    void Update(double xAccel, double yAccel);
    
};

#endif /* defined(__INSTest__INSBase__) */
