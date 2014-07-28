#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "metric.h"
#include "utils.h"
#include "solver.h"
# define PI 3.14159265358979323846

int speed(int ni, int nj, float fsmach, float alpha, double tol, bool iread, int integrator){
  
  float gamma = 1.4;
  int nim = ni - 1;
  int njm = nj - 1;
  
  // read grid, grid is generated in fortran therefore j index should be the outer index
  double x[ni][nj], y[ni][nj];
  readgrid(ni, nj, x, y);
  
  
  // declare metric variables
  double xc[nim][njm], yc[nim][njm], vol[nim][njm], ds_eta[nim][njm], ds_xi[nim][njm];
  double neta_x[nim][nj], neta_y[nim][nj];
  double nxi_x[ni][njm], nxi_y[ni][njm];
  // calculate metric
  metric(ni, nj, x, y, neta_x, neta_y, nxi_x, nxi_y, vol, xc, yc, ds_eta, ds_xi);
  
  // define freestream conditions
  state freestream;
  freestream.rho = 1.0;
  freestream.u = fsmach*cos(alpha*PI/180);
  freestream.v = fsmach*sin(alpha*PI/180);
  freestream.p = 1/1.4;
  freestream.mach = fsmach;
  freestream.alpha = alpha*PI/180;
  // declare the conservative vector Q
  double Q[nim][njm][4];
  
  double res_rho;
  // this intializes the domain, see iread = true or false
  init(ni, nj, Q, freestream, gamma, iread);
  solver(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, vol, xc, yc, ds_eta, ds_xi, freestream, tol, integrator, gamma);
  
  return 0;

}
