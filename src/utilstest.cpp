#include "utils.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
  double rho[2], u[2], v[2], p[2];
  double Q[2][4];
  double gamma = 1.4;
  Q[0][0] = 1.1;
  Q[1][0] = 1.0;
  Q[:][1] = 0.5;
  Q[:][2] = 0.25;
  Q[:][3] = 1.9;
  primvars(Q[:], gamma, &rho[:], &u[:], &v[:], &p[:]);
  printf("%f\n", rho[:]);
  printf("%f\n", u[:]);
  printf("%f\n", v[:]);
  printf("%f\n", p[:]);
  return 0;
 
}
