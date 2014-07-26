#ifndef _INCL_METRIC
#define _INCL_METRIC
#include <stdio.h>
#include <cmath>
// TEST STATUS: CHECKED DEFCON 1

void metric(int ni, int nj, double x[ni][nj], double y[ni][nj], double neta_x[ni-1][nj], double neta_y[ni-1][nj], \
	    double nxi_x[ni][nj-1], double nxi_y[ni][nj-1], double vol[ni-1][nj-1], \
	    double xc[ni-1][nj-1], double yc[ni-1][nj-1],		\
	    double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1]){

  // Calculate face normals, cell volume, and cell center
  // Number of cells = (ni-1) x (nj-1) and faces are numbered accordingly

  // xi direction is in increasing i
  // eta direction is in increasing j
  // xi drection is the wrap around direction, eta is normal to the body

  int nim = ni-1;
  int njm = nj-1;
  double reta_x[nim][nj], reta_y[nim][nj];
  double rxi_x[ni][njm], rxi_y[ni][njm];

  reta_x[0:nim][0:nj] = x[1:nim][0:nj] - x[0:nim][0:nj];
  reta_y[0:nim][0:nj] = y[1:nim][0:nj] - y[0:nim][0:nj];

  rxi_x[0:ni][0:njm] = x[0:ni][1:njm] - x[0:ni][0:njm];
  rxi_y[0:ni][0:njm] = y[0:ni][1:njm] - y[0:ni][0:njm];


  neta_x[0:nim][0:nj] = -reta_y[0:nim][0:nj];
  neta_y[0:nim][0:nj] = reta_x[0:nim][0:nj];

  
  nxi_x[0:ni][0:njm] = rxi_y[0:ni][0:njm];
  nxi_y[0:ni][0:njm] = -rxi_x[0:ni][0:njm];

  vol[0:nim][0:njm] = 0.5*(reta_x[0:nim][0:njm]*rxi_y[0:nim][0:njm] - rxi_x[0:nim][0:njm]*reta_y[0:nim][0:njm] \
			   + reta_x[0:nim][1:njm]*rxi_y[1:nim][0:njm] - rxi_x[1:nim][0:njm]*reta_y[0:nim][1:njm]);


  xc[0:nim][0:njm] = 0.25*(x[0:nim][0:njm] + x[1:nim][0:njm] + x[0:nim][1:njm] + x[1:nim][1:njm]);
  yc[0:nim][0:njm] = 0.25*(y[0:nim][0:njm] + y[1:nim][0:njm] + y[0:nim][1:njm] + y[1:nim][1:njm]);

  ds_eta[0:nim][0:njm] = sqrt(pow(neta_x[0:nim][0:njm],2) + pow(neta_y[0:nim][0:njm],2));
  ds_xi[0:nim][0:njm] = sqrt(pow(nxi_x[0:nim][0:njm],2) + pow(nxi_y[0:nim][0:njm],2));
  
}

#endif
