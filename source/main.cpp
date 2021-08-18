#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"

const f64 MaxJerk         = 10.0;
const f64 MaxAcceleration = 2;
const f64 MaxVelocity     = 1;

#include "integration.cpp"
#include "motion_profile.cpp"

#include "testing.cpp"

//~ Main

int main() {
 //~ Test everything:
 TestPositionMotionProfile1D( 123);
 TestPositionMotionProfile1D(-456);
 
 TestVelocityMotionProfile1D( 123);
 TestVelocityMotionProfile1D(-456);
 
 TestPositionMotionProfile2D(V2(123, 456));
 
 
 // NOTE(Tyler): So it runs in the debugger without closing immediately
 printf("\n\n");
 system("pause");
}
