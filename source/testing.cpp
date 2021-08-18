
//~ Testing
void
TestPositionMotionProfile1D(f64 Target){
 printf("\n---------------------------------------\n");
 printf(  "  Test 1D motion profile for position  \n");
 printf(  "---------------------------------------\n\n");
 printf("Target: %f\n", Target);
 
 motion_profile_1d Profile = {};
 CalculatePositionMotionProfile1D(&Profile, Target, MaxJerk, MaxAcceleration, MaxVelocity);
 
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
TestVelocityMotionProfile1D(f64 Target){
 printf("\n---------------------------------------\n");
 printf(  "  Test 1D motion profile for velocity  \n");
 printf(  "---------------------------------------\n\n");
 printf("Target: %f\n", Target);
 
 motion_profile_1d Profile = {};
 CalculateVelocityMotionProfile1D(&Profile, Target, MaxJerk, MaxAcceleration);
 
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
 
 integration_context Context = MakeIntegrationContext(0.0001, t3, MaxAcceleration, MaxVelocity);
 
 while(IntegrationDoContinue(&Context)){
  f64 JerkForStep = 0.0;
  if(Context.CurrentTime <= t0){
  }else if(Context.CurrentTime <= t1){
   JerkForStep = Jerk;
  }else if(Context.CurrentTime <= t2){
   JerkForStep = 0.0;
  }else if(Context.CurrentTime <= t3){
   JerkForStep = -Jerk;
  }
  
  IntegrationStep(&Context, JerkForStep);
 }
 
 IntegrationPrintResults(&Context);
 
}