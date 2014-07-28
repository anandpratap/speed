#ifndef _INCL_UTILS
#define _INCL_UTILS
#include <stdio.h>

struct state{
  double rho, u, v, p, mach, alpha;
};

struct result{
  double Cl, Cd;
};

// TEST STATUS: Checked, DEFCON 3
// see utilstest on how to use it
// this is a simd function
__declspec(vector) void primvars(double Q[4], float gamma, double *rho, double *u, double *v, double *p);


// TEST STATUS: Not tested
void init(int ni, int nj, double Q[ni-1][nj-1][4], struct state freestream, float gamma=1.4, bool restart=false);

#endif
