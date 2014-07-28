#ifndef _INCL_FORCE
#define _INCL_FORCE
#include "utils.h"
void force(int ni, int nj, double Q[ni-1][nj-1][4],			\
	   double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	   double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	   double xc[ni-1][nj-1], double yc[ni-1][nj-1],		\
	   struct state freestream, double gamma);
	   

#endif
