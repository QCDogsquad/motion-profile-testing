#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"

const f64 MaxJerk         = 10.0;
const f64 MaxAcceleration = 2;
const f64 MaxVelocity     = 1;

#include "integration.cpp"
#include "motion_profile.cpp"

//~ Main

int main() {
 motion_profile_1d Profile = {};
 
 f64 Jerk = Profile.Jerk;
 
 f64 tr = Profile.tr;
 f64 th = Profile.th;
 f64 tw = Profile.tw;
 
 printf("r: %f\n", tr);
 printf("h: %f\n", th);
 printf("w: %f\n", tw);
 
 f64 t0 = 0.0;
 f64 t1 = t0 + Profile.tr;
 f64 t2 = t1 + Profile.th;
 f64 t3 = t2 + Profile.tr;
 f64 t4 = t3;
 f64 t5 = t3;
 f64 t6 = t3;
 f64 t7 = t3;
 
 if(Profile.Type == MotionProfile_Position){
  t4 = t3 + Profile.tw;
  t5 = t4 + Profile.tr;
  t6 = t5 + Profile.th;
  t7 = t6 + Profile.tr;
 }
 
 integration_context Context = MakeIntegrationContext(0.0001, t7, MaxAcceleration, MaxVelocity);
 
 // TODO(Tyler): It would likely be better to use something like RK4 
 // instead of basic Euler integration
 while(IntegrationDoContinue(&Context)){
  f64 JerkForStep = 0.0;
  if(Context.CurrentTime <= t0){
  }else if(Context.CurrentTime <= t1){
   JerkForStep = Jerk;
  }else if(Context.CurrentTime <= t2){
   JerkForStep = 0.0;
  }else if(Context.CurrentTime <= t3){
   JerkForStep = -Jerk;
  }else if(Context.CurrentTime <= t4){
   JerkForStep = 0.0;
  }else if(Context.CurrentTime <= t5){
   JerkForStep = -Jerk;
  }else if(Context.CurrentTime <= t6){
   JerkForStep = 0.0;
  }else if(Context.CurrentTime <= t7){
   JerkForStep = Jerk;
  }
  
  IntegrationStep(&Context, JerkForStep);
 }
 
 IntegrationPrintResults(&Context);
 
 f64 s0 = 0.0, v0 = 0.0, a0 = 0.0;
 f64 v3 = v0 + Jerk*square(tr) + Jerk*tr*th;
 
 f64 v7 = v0;
 f64 s7 = s0 + v3*tw + 3*Jerk*square(tr)*th + 2*Jerk*cube(tr) + Jerk*tr*square(th);
 printf("\nPredicted Velocity: %f\n", v7);
 printf(  "Predicted Position: %f\n", s7);
 
 
 
 //~ Test everything:
 TestMotionProfile1DPosition( 123);
 TestMotionProfile1DPosition(-456);
 TestMotionProfile1DVelocity( 123);
 TestMotionProfile1DVelocity(-456);
 
 
 
 // NOTE(Tyler): So it runs in the debugger without closing immediately
 printf("\n\n");
 system("pause");
}
