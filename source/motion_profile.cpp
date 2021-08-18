
//~ 1D motion profiles
void 
CalculatePositionMotionProfile1D(motion_profile_1d *Profile, 
                                 f64 TargetPosition, f64 Jerk, 
                                 f64 MaxAcceleration_, f64 MaxVelocity_) {
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
CalculateVelocityMotionProfile1D(motion_profile_1d *Profile,
                                 f64 TargetVelocity, f64 Jerk, f64 MaxAcceleration_) {
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

//~ 2D motion profiles
void CalculatePositionMotionProfile2D(){
 
}