#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "metric.h"
#include "utils.h"
#include "solver.h"
int main(void){
  int ni, nj;
  ni = 281;
  nj = 51;
  
  double gamma = 1.4;
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
  freestream.u = 0.5;
  freestream.v = 0.0;
  freestream.p = 1/1.4;
  
  // declare the conservative vector Q
  double Q[nim][njm][4];
  
  double res_rho;
  bool iread = false;
  // this intializes the domain, see iread = true or false
  init(ni, nj, Q, freestream, gamma, iread);

  
  
  solver(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, vol, xc, yc, ds_eta, ds_xi, freestream, 1e-6, 1, gamma);
  writedata(ni, nj, Q, xc, yc);
  return 0;
}
