/* date = August 17th 2021 7:57 pm */

#ifndef INTEGRATION_H
#define INTEGRATION_H

struct integration_context {
 f64 Position     = 0.0;
 f64 Velocity     = 0.0;
 f64 Acceleration = 0.0;
 
 f64 TheoreticalMaxAcceleration = 0.0f;
 f64 TheoreticalMaxVelocity = 0.0f;
 
 f64 MaxFoundAcceleration = -INFINITY;
 f64 MaxFoundVelocity     = -INFINITY;
 f64 MinFoundAcceleration = INFINITY;
 f64 MinFoundVelocity     = INFINITY;
 
 f64 CurrentTime = 0.0f;
 
 f64 dTime = 0.0001;
 f64 EndTime = 0.0;
};

#endif //INTEGRATION_H
