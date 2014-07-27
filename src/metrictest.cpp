#include "metric.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
int main(void){
  int ni = 2;
  int nj = 2;
  double x[ni][nj], y[ni][nj];
  double dx = 0.5;
  double dy = 1.5;

  x[0][0] = 0.0;
  y[0][0] = 0.0;

  x[1][0] = dx;
  y[1][0] = 0.0;

  x[0][1] = 0.0;
  y[0][1] = dy;

  x[1][1] = 2*dx;
  y[1][1] = 2*dy;

  double neta_x[ni-1][nj], neta_y[ni-1][nj], nxi_x[ni][nj-1], nxi_y[ni][nj-1];
  double vol[ni-1][nj-1], xc[ni-1][nj-1], yc[ni-1][nj-1];
  double ds_eta[ni-1][nj-1], ds_xi[ni-1][nj-1];
  metric(ni, nj, x, y, neta_x, neta_y, nxi_x, nxi_y, vol, xc, yc, ds_eta, ds_xi);
  std::cout<<ds_eta[0][0]<<" "<< ds_xi[0][0]<<"\n";
  std::cout<<vol[0][0]<<"\n";
  // assert(std::abs(xc[0][0] - dx/2.0) < 1e-10);
  // assert(std::abs(yc[0][0] - dy/2.0) < 1e-10);
  // assert(std::abs(neta_x[0][0])<1e-10);
  // assert(std::abs(neta_x[0][1])<1e-10);
  // assert(std::abs(nxi_y[0][0])<1e-10);
  // assert(std::abs(nxi_y[1][0])<1e-10);
  // assert(std::abs(vol[0][0]-dx*dy)<1e-10);
  return 0;

}
