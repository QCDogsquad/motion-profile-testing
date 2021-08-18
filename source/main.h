/* date = August 16th 2021 7:20 pm */

#ifndef MAIN_H
#define MAIN_H

#include "tyler_basics.h"
#include "tyler_math.h"

#include "integration.h"


enum motion_profile_1d_type {
 MotionProfile_Position,
 MotionProfile_Velocity,
};

struct motion_profile_1d {
 motion_profile_1d_type Type;
 f64 Jerk;
 f64 tr; // The period of interrupted time where jerk is non-zero
 f64 th; // The period of interrupted time where acceleration is constant and non-zero
 f64 tw; // The period of interrupted time where acceleration is zero
};


#endif //MAIN_H
