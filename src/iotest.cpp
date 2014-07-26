#include "io.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
int main(void){
  int ni = 281;
  int nj = 51;
  double x[ni][nj], y[ni][nj];
  readgrid(ni, nj, x, y);
  std::ofstream outfile;
  outfile.open("iotest.dat");
  char buffer [50];
  for(int i=0; i<ni; i++){
    sprintf(buffer, "%E %E\n", x[i][0], y[i][0]);
    outfile << buffer;  // should be the airfoil surface
  }
  outfile.close();
  return 0;
 
}
