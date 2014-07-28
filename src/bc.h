#ifndef _INCL_BC
#define _INCL_BC

#include "utils.h"
#include <cmath>

// TEST STATUS: Not tested, but should work fine
void bc(int ni, int nj, double Q[ni-1][nj-1][4],			\
	double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1], \
	double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	struct state freestream, float gamma=1.4);

#endif
