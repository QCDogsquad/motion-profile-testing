/* date = August 16th 2021 7:21 pm */

#ifndef TYLER_MATH_H
#define TYLER_MATH_H
inline f64
square(f64 A)
{
 f64 Result = A*A;
 return(Result);
}

inline f64
cube(f64 A)
{
 f64 Result = A*A*A;
 return(Result);
}

inline f64
tesseract(f64 A)
{
 f64 Result = A*A*A*A;
 return(Result);
}

inline f64
clamp(f64 Value, f64 Min, f64 Max){
 f64 Result = Value;
 if(Result < Min){
  Result = Min;
 }else if(Result > Max){
  Result = Max;
 }
 return(Result);
}

inline f64
round(f64 A)
{
 f64 Result;
 if(A < 0)
 {
  Result = floor((A - 0.5f));
 }
 else
 {
  Result = floor((A + 0.5f));
 }
 return(Result);
}

inline f64
sign_of(f64 A){
 f64 Result = (A < 0) ? -1.0f : 1.0f;
 return(Result);
}

inline f64
lerp(f64 A, f64 B, f64 T){
 T = clamp(T, 0.0f, 1.0f);
 f64 Result = T*A + (1.0f-T)*B;
 return(Result);
}

inline s32
normalize_degrees(s32 D){
 s32 Result;
 if(D < 0){
  Result = D;
  while(Result < 0) Result += 360; 
 }else{
  Result = D % 360;
 }
 return(Result);
}

//~ V2s

union V2
{
 struct
 {
  f64 X;
  f64 Y;
 };
 struct
 {
  f64 Width;
  f64 Height;
 };
};

inline V2
v2(f64 X, f64 Y){ 
 V2 Result = V2{X, Y}; 
 return(Result);
}

inline V2
v2(f64 XY){ 
 V2 Result = v2(XY, XY); 
 return(Result);
}

typedef union V2s V2s;
union V2s
{
 struct
 {
  s32 X;
  s32 Y;
 };
 struct
 {
  s32 Width;
  s32 Height;
 };
};

inline V2
v2(V2s A){ 
 V2 Result = V2{(f64)A.X, (f64)A.Y}; 
 return(Result);
}

inline V2
operator+(V2 A, V2 B)
{
 V2 Result;
 Result.X = A.X + B.X;
 Result.Y = A.Y + B.Y;
 return(Result);
}

inline V2
operator-(V2 A, V2 B)
{
 V2 Result;
 Result.X = A.X - B.X;
 Result.Y = A.Y - B.Y;
 return(Result);
}

inline V2
operator-(V2 A)
{
 V2 Result;
 Result.X = -A.X;
 Result.Y = -A.Y;
 return(Result);
}

inline V2
operator*(V2 A, f64 B)
{
 V2 Result;
 Result.X = A.X * B;
 Result.Y = A.Y * B;
 return(Result);
}

inline V2
operator*(f64 B, V2 A)
{
 V2 Result;
 Result.X = A.X * B;
 Result.Y = A.Y * B;
 return(Result);
}

inline V2
operator/(V2 A, f64 B)
{
 V2 Result;
 Result.X = A.X / B;
 Result.Y = A.Y / B;
 return(Result);
}

inline V2
operator+=(V2 &A, V2 B)
{
 A = A + B;
 return(A);
}

inline V2
operator-=(V2 &A, V2 B)
{
 A = A - B;
 return(A);
}

inline V2
operator*=(V2 &A, f64 B)
{
 A = B * A;
 return(A);
}

inline V2
operator/=(V2 &A, f64 B)
{
 A = A / B;
 return(A);
}

inline f64
dot(V2 A, V2 B) {
 f64 Result = (A.X*B.X)+(A.Y*B.Y);
 return(Result);
}

inline V2
hadamard(V2 A, V2 B){
 V2 Result;
 Result.X = A.X*B.X;
 Result.Y = A.Y*B.Y;
 return(Result);
}

inline f64
length_squared(V2 V){
 f64 Result = dot(V, V);
 return(Result);
}

inline f64
length(V2 V){
 f64 Result = sqrt(length_squared(V));
 return(Result);
}

inline V2
normalize(V2 V){
 f64 l = length(V);
 V2 Result = {};
 if(l > 0.0f){
  Result = V/l;
 }
 return(Result);
}

// Perpendicular to A in the direction of B
inline V2 
triple_product_V2(V2 A, V2 B){
 // A cross B cross A = (A cross B) cross A
 f64 Z = (A.X*B.Y)-(A.Y*B.X);
 V2 Result = v2(-Z*A.Y, Z*A.X);
 return(Result);
}

inline V2
minimum_V2(V2 A, V2 B){
 V2 Result;
 Result.X = Minimum(A.X, B.X);
 Result.Y = Minimum(A.Y, B.Y);
 
 return(Result);
}

inline V2
maximum_V2(V2 A, V2 B){
 V2 Result;
 Result.X = Maximum(A.X, B.X);
 Result.Y = Maximum(A.Y, B.Y);
 
 return(Result);
}

V2
square_v2(V2 V){
 V2 Result;
 Result.X = V.X*V.X;
 Result.Y = V.Y*V.Y;
 return(Result);
}

inline V2
floor_V2(V2 V){
 V2 Result;
 Result.X = floor(V.X);
 Result.Y = floor(V.Y);
 return(Result);
}

inline V2
round_V2(V2 V){
 V2 Result;
 Result.X = round(V.X);
 Result.Y = round(V.Y);
 return(Result);
}

inline V2
ceil_V2(V2 V){
 V2 Result;
 Result.X = ceil(V.X);
 Result.Y = ceil(V.Y);
 return(Result);
}

inline V2
lerp(V2 A, V2 B, f64 T){
 T = clamp(T, 0.0f, 1.0f);
 V2 Result = T*A + (1.0f-T)*B;
 return(Result);
}
#endif //TYLER_MATH_H
