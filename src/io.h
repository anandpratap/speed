#ifndef _INCL_IO
#define _INCL_IO
#include <fstream>
#include <iostream>
#include <iomanip>
#include "stdio.h"
#include "utils.h"
void readgrid(int ni, int nj, double x[ni][nj], double y[ni][nj]){
  std::ifstream infile("grid.unf2");
  infile >> std::fixed >> std::setprecision(20);
  double xx, yy;
for(int j=0; j<nj; j++){
 for(int i=0; i<ni; i++){  
      infile>>x[i][j]>>y[i][j];
    }
  }
}
  

void writedata(int ni, int nj, double Q[ni-1][nj-1][4], double xc[ni-1][nj-1], double yc[ni-1][nj-1]){
  int nim = ni - 1;
  int njm = nj - 1;
  double gamma = 1.4;
  double rho[nim][njm], u[nim][njm], v[nim][njm], p[nim][njm];

  primvars(Q[:][:], gamma, &rho[:][:], &u[:][:], &v[:][:], &p[:][:]);

  std::ofstream outfile;
  outfile.open("data.dat");
  char buffer [500];
  for(int i=0; i<nim; i++){
    for(int j=0; j<njm; j++){
      sprintf(buffer, "%d %d %8.14E %8.14E %8.14E %8.14E %8.14E %8.14E\n", i,j,xc[i][j], yc[i][j], rho[i][j], u[i][j], v[i][j], p[i][j]);
      outfile<<buffer;
    }
  }
  outfile.close();
  printf("Data dumped..\n");
}

#endif
