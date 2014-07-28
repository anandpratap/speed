#ifndef _INCL_INTEGRATOR
#define _INCL_INTEGRATOR
#include "residual.h"

void euler(int ni, int nj, double Q[ni-1][nj-1][4],			\
	   double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	   double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	   double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], \
	   struct state freestream, double* res_rho, float gamma = 1.4);

void jst(int ni, int nj, double Q[ni-1][nj-1][4],			\
	 double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	 double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	 double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], \
	 struct state freestream, double* res_rho, float gamma = 1.4);


void rk2(int ni, int nj, double Q[ni-1][nj-1][4],			\
	 double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	 double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	 double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], \
	 struct state freestream, double* res_rho, float gamma = 1.4);


#endif
