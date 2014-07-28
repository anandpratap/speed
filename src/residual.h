#ifndef _INCL_RESIDUAL
#define _INCL_RESIDUAL
#include "bc.h"
#include "utils.h"
#include "recon.h"
#include "flux.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cilk/cilk.h>

// Confession: the default abs() function returns only integer, used <cmath> and std::abs()
//             wasted a day because of this stupid function

void residual(int ni, int nj, double Q[ni-1][nj-1][4],			\
	      double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	      double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	      double res[ni-1][nj-1][4], double vol[ni-1][nj-1],	\
	      double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1],	\
	      double dt[ni-1][nj-1],struct state freestream,		\
	      float gamma=1.4);

#endif
