#include "flux.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
  double gamma = 1.4;
  double rho[2][2], u[2][2], v[2][2], p[2][2], f[2][2][4];
  f[:][:][:] = 10.0;
  rho[:][:] = 1.0;
  rho[0][0] = 2.0;
  rho[1][0] = 1.1;

  u[:][:] = 1.0;
  v[:][:] = 1.0;
  p[:][:] = 1/gamma;
  double nx =  0.5;
  double ny = 0.5;
  roeflux(nx, ny, rho[:][:], u[:][:], v[:][:], p[:][:], rho[:][:], u[:][:], v[:][:], p[:][:], gamma, f[:][:]);
  printf("%f\n", f[:][:][0]);
  // assert(abs(f[:][:][0]-1.0) < 1e-10);
  printf("%f\n", f[:][:][1]);
  //assert(abs(f[:][:][1]-1.3571) < 1e-10);
  printf("%f\n", f[:][:][2]);
  //assert(abs(f[:][:][2]-1.3571) < 1e-10);
  printf("%f\n", f[:][:][3]);
  //assert(abs(f[:][:][3]-3.5) < 1e-10);
  

  return 0;

}
