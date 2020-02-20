void XYZtoBLH(double X, double Y, double Z) 
{

#include "stdio.h"
#include "string.h"
#include "math.h"
#include "stdlib.h"

#define aAxis 6378137
#define bAxis 6356752.314
#define PI 3.1415926535897932384626433832795

  double e1,e2,S,cosL,B=0.0,L=0.0;
  double c,preB0=0.0,ll=0.0,N=0.0;
  double tanB;
  double  targetZ, targetL,targetB;
  
  e1 = (pow(aAxis, 2) - pow(bAxis, 2)) / pow(aAxis, 2);
  e2 = (pow(aAxis, 2) - pow(bAxis, 2)) / pow(bAxis, 2);
	 
  S = sqrt(pow(X, 2) + pow(Y, 2));
  // cosL = X / S
  
  L = fabs(acos(X/S)); 
  // tanB = Z / S;
  B = atan(X/S);
  c = aAxis * aAxis / bAxis;
  
  //迭代计算纬度
  do {
    preB0 = B;
    ll = pow(cos(B), 2) * e2;
    N = c / sqrt(1 + ll);
    
    tanB = (Z + N * e1 * sin(B)) / S;
    B = .atan(tanB);
  }
  while (fabs(preB0 - B) >= 0.0000000001);
  
  ll = pow(Math.cos(B), 2) * e2;
  N = c / sqrt(1 + ll);
	 
  targetZ = Z / sin(B) - N * (1 - e1);
  targetB = B * 180 / PI;
  targetL = L * 180 / PI;
}
