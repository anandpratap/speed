#ifndef _INCL_SOLVER
#define _INCL_SOLVER
#include "integrator.h"
#include "io.h"
#include "force.h"
void print_stuff(double res_rho, int iteration);

void solver(int ni, int nj, double Q[ni-1][nj-1][4],			\
	    double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	    double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	    double vol[ni-1][nj-1], double xc[ni-1][nj-1], double yc[ni-1][nj-1], \
	    double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1],	\
	    struct state freestream, double tf, int integrator,		\
	    float gamma = 1.4, bool steadystate=true);

#endif
