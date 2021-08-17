#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "main.h"

void CalculateMotionProfileForPosition(f64 TargetPosition, f64 Jerk, 
                                       f64 MaxAcceleration, f64 MaxVelocity, 
                                       motion_profile *Profile) {
 *Profile = {};
 Profile->Type = MotionProfile_Position;
 
 if(TargetPosition < 0) Profile->Jerk = -Jerk; 
 else                   Profile->Jerk =  Jerk;
 TargetPosition = fabs(TargetPosition);
 
 f64 tz = Minimum(MaxAcceleration/Jerk, sqrt((MaxVelocity)/Jerk));
 f64 ty = (MaxVelocity - Jerk*square(tz)) / (Jerk*tz);
 
 f64 Initial_tr = cbrt(TargetPosition/(2*Jerk));
 if(Initial_tr > tz){
  Profile->tr = tz;
  
  f64 b = Jerk*square(tz);
  f64 c = -TargetPosition;
  f64 Initial_th = (-b + sqrt(square(b) - 4*Jerk*tz*c))/(2*Jerk*tz) - tz;
  
  if(Initial_th > ty){
   Profile->th = ty;
   Profile->tw = (TargetPosition - Jerk*cube(tz) - Jerk*square(tz)*ty) / (Jerk*square(tz) + Jerk*tz*ty) - tz - ty;
  }else{
   Profile->th = Initial_th;
   Profile->tw = 0.0;
  }
 }else{
  Profile->tr = Initial_tr;
  Profile->th = 0.0;
  Profile->tw = 0.0;
 }
}

void CalculateMotionProfileForVelocity(f64 TargetVelocity, 
                                       f64 Jerk, f64 MaxAcceleration,
                                       motion_profile *Profile) {
 *Profile = {};
 Profile->Type = MotionProfile_Velocity;
 
 if(TargetVelocity < 0) Profile->Jerk = -Jerk; 
 else                   Profile->Jerk =  Jerk;
 TargetVelocity = fabs(TargetVelocity);
 
 f64 tz = MaxAcceleration/Jerk;
 f64 Initial_tr = sqrt(TargetVelocity/Jerk);
 if(Initial_tr > tz){
  Profile->tr = tz;
  Profile->th = TargetVelocity/(Jerk*tz) - tz;
 }else{
  Profile->tr = Initial_tr;
  Profile->th = 0.0;
 }
}

int main() {
 const f64 MaxJerk         = 10.0;
 const f64 MaxAcceleration = 2;
 const f64 MaxVelocity     = 1;
 
 motion_profile Profile = {};
 CalculateMotionProfileForPosition(-123, MaxJerk, MaxAcceleration, MaxVelocity, &Profile);
 //CalculateMotionProfileForVelocity(123, MaxJerk, MaxAcceleration, &Profile);
 
 f64 Jerk = Profile.Jerk;
 
 f64 Position     = 0.0;
 f64 Velocity     = 0.0;
 f64 Acceleration = 0.0;
 
 f64 CurrentTime = 0.0;
 f64 dTime       = 0.0001;
 
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
 
 f64 EndTime = t7;
 
 f64 MaxFoundAcceleration = -INFINITY;
 f64 MaxFoundVelocity     = -INFINITY;
 f64 MinFoundAcceleration = INFINITY;
 f64 MinFoundVelocity     = INFINITY;
 
 while(CurrentTime < EndTime+dTime){
  f64 Jerk_for_step = 0.0;
  if(CurrentTime <= t0){
  }else if(CurrentTime <= t1){
   Jerk_for_step = Jerk;
  }else if(CurrentTime <= t2){
   Jerk_for_step = 0.0;
  }else if(CurrentTime <= t3){
   Jerk_for_step = -Jerk;
  }else if(CurrentTime <= t4){
   Jerk_for_step = 0.0;
  }else if(CurrentTime <= t5){
   Jerk_for_step = -Jerk;
  }else if(CurrentTime <= t6){
   Jerk_for_step = 0.0;
  }else if(CurrentTime <= t7){
   Jerk_for_step = Jerk;
  }
  
  Position += (Velocity*dTime +
               0.5*Acceleration*square(dTime) + 
               (1.0/6.0)*Jerk_for_step*cube(dTime) );
  Velocity += (Acceleration*dTime +
               0.5*Jerk_for_step*square(dTime) );
  Acceleration += Jerk_for_step*dTime;
  
  if(Acceleration > MaxFoundAcceleration) MaxFoundAcceleration = Acceleration;
  if(Acceleration < MinFoundAcceleration) MinFoundAcceleration = Acceleration;
  
  if(Velocity > MaxFoundVelocity) MaxFoundVelocity = Velocity;
  if(Velocity < MinFoundVelocity) MinFoundVelocity = Velocity;
  
  CurrentTime += dTime;
 }
 
 f64 tr = Profile.tr;
 f64 th = Profile.th;
 f64 tw = Profile.tw;
 
 printf("r: %f\n", tr);
 printf("h: %f\n", th);
 printf("w: %f\n", tw);
 printf("Final time: %f\n", CurrentTime-dTime);
 printf("Total time: %f\n", EndTime);
 
 printf("\ntheoretical min and max Acceleration: %f %f\n", -MaxAcceleration, MaxAcceleration);
 printf(  "Actual min and max Acceleration:      %f %f\n", MinFoundAcceleration, MaxFoundAcceleration);
 printf(  "Theoretical min and max Velocity:     %f %f\n", -MaxVelocity, MaxVelocity);
 printf(  "Actual min and max Velocity:          %f %f\n", MinFoundVelocity, MaxFoundVelocity);
 
 printf("\nFinal Position:     %f\n", Position);
 printf(  "Final Velocity:     %f\n", Velocity);
 printf(  "Final Acceleration: %f\n", Acceleration);
 
 f64 s0 = 0.0, v0 = 0.0, a0 = 0.0;
 f64 v3 = v0 + Jerk*square(tr) + Jerk*tr*th;
 
 f64 v7 = v0;
 f64 s7 = s0 + v3*tw + 3*Jerk*square(tr)*th + 2*Jerk*cube(tr) + Jerk*tr*square(th);
 printf("\nPredicted Velocity: %f\n", v7);
 printf(  "Predicted Position: %f\n", s7);
 
 
 printf("\n\n");
 system("pause");
}
