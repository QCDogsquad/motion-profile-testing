
//~ 1D motion profiles
void 
CalculateMotionProfile1DForPosition(f64 TargetPosition, f64 Jerk, 
                                    f64 MaxAcceleration_, f64 MaxVelocity_, 
                                    motion_profile_1d *Profile) {
 *Profile = {};
 Profile->Type = MotionProfile_Position;
 
 if(TargetPosition < 0) Profile->Jerk = -Jerk; 
 else                   Profile->Jerk =  Jerk;
 TargetPosition = fabs(TargetPosition);
 
 f64 tz = Minimum(MaxAcceleration_/Jerk, sqrt((MaxVelocity_)/Jerk));
 f64 ty = (MaxVelocity_ - Jerk*square(tz)) / (Jerk*tz);
 
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

void 
CalculateMotionProfile1DForVelocity(f64 TargetVelocity, 
                                    f64 Jerk, f64 MaxAcceleration_,
                                    motion_profile_1d *Profile) {
 *Profile = {};
 Profile->Type = MotionProfile_Velocity;
 
 if(TargetVelocity < 0) Profile->Jerk = -Jerk; 
 else                   Profile->Jerk =  Jerk;
 TargetVelocity = fabs(TargetVelocity);
 
 f64 tz = MaxAcceleration_/Jerk;
 f64 Initial_tr = sqrt(TargetVelocity/Jerk);
 if(Initial_tr > tz){
  Profile->tr = tz;
  Profile->th = TargetVelocity/(Jerk*tz) - tz;
 }else{
  Profile->tr = Initial_tr;
  Profile->th = 0.0;
 }
}


//~ Testing
void
TestMotionProfile1DPosition(f64 Target){
 printf("\n---------------------------------------\n");
 printf(  "  Test 1D motion profile for position  \n");
 printf(  "---------------------------------------\n\n");
 printf("Target: %f\n", Target);
 
 motion_profile_1d Profile = {};
 CalculateMotionProfile1DForPosition(Target, MaxJerk, MaxAcceleration, MaxVelocity, &Profile);
 
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
}


void
TestMotionProfile1DVelocity(f64 Target){
 printf("\n---------------------------------------\n");
 printf(  "  Test 1D motion profile for velocity  \n");
 printf(  "---------------------------------------\n\n");
 printf("Target: %f\n", Target);
 
 motion_profile_1d Profile = {};
 CalculateMotionProfile1DForVelocity(Target, MaxJerk, MaxAcceleration, &Profile);
 
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
 
}