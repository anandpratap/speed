#ifndef _INCL_METRIC
#define _INCL_METRIC
#include <stdio.h>
#include <cmath>
// TEST STATUS: CHECKED DEFCON 1

void metric(int ni, int nj, double x[ni][nj], double y[ni][nj], double neta_x[ni-1][nj], double neta_y[ni-1][nj], \
	    double nxi_x[ni][nj-1], double nxi_y[ni][nj-1], double vol[ni-1][nj-1], \
	    double xc[ni-1][nj-1], double yc[ni-1][nj-1],		\
	    double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1]);

#endif
