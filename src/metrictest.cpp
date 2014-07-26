#include "metric.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
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

  x[1][1] = dx;
  y[1][1] = dy;

  double neta_x[ni-1][nj], neta_y[ni-1][nj], nxi_x[ni][nj-1], nxi_y[ni][nj-1];
  double vol[ni-1][nj-1], xc[ni-1][nj-1], yc[ni-1][nj-1];
  
  metric(ni, nj, x, y, neta_x, neta_y, nxi_x, nxi_y, vol, xc, yc);
 
  assert(abs(xc[0][0] - dx/2.0) < 1e-10);
  assert(abs(yc[0][0] - dy/2.0) < 1e-10);
  assert(abs(neta_x[0][0])<1e-10);
  assert(abs(neta_x[0][1])<1e-10);
  assert(abs(nxi_y[0][0])<1e-10);
  assert(abs(nxi_y[1][0])<1e-10);
  assert(abs(vol[0][0]-dx*dy)<1e-10);
  return 0;

}
