#ifndef _INCL_UTILS
#define _INCL_UTILS
#include <stdio.h>

// TEST STATUS: Checked, DEFCON 3
// see utilstest on how to use it
__declspec(vector) void primvars(double Q[4], double gamma, double *rho, double *u, double *v, double *p){
  *rho = Q[0];
  *u = Q[1]/Q[0];
  *v = Q[2]/Q[0];
  *p = (Q[3] - 0.5*(Q[1]*Q[1] + Q[2]*Q[2])/Q[0])*(gamma-1);
}

#endif
