#ifndef _INCL_UTILS
#define _INCL_UTILS
#include <stdio.h>

struct state{
  double rho, u, v, p, mach, alpha;
};


// TEST STATUS: Checked, DEFCON 3
// see utilstest on how to use it
// this is a simd function
__declspec(vector) void primvars(double Q[4], double gamma, double *rho, double *u, double *v, double *p){
  double tmp_rho = Q[0];
  double tmp_u = Q[1]/tmp_rho;
  double tmp_v = Q[2]/tmp_rho;
  *rho = Q[0];
  *u = Q[1]/Q[0];
  *v = Q[2]/Q[0];
  *p = (Q[3] - 0.5*tmp_rho*(tmp_u*tmp_u + tmp_v*tmp_v))*(gamma-1);
}





// TEST STATUS: Not tested
void init(int ni, int nj, double Q[ni-1][nj-1][4], struct state freestream, double gamma=1.4, bool restart=false){
  int nim = ni - 1;
  int njm = nj - 1;
  double rho[nim][njm], u[nim][njm], v[nim][njm], p[nim][njm];
  
  if(restart){
  
    std::ifstream infile("data.dat");
    double tmp;
    int itmp;
    for(int i=0; i<nim; i++){
      for(int j=0; j<njm; j++){
	infile>>itmp>>itmp>>tmp>>tmp>>rho[i][j]>>u[i][j]>>v[i][j]>>p[i][j];
      }
    }
  
  }
  else{
  
    rho[:][:] = freestream.rho;
    u[:][:] = freestream.u;
    v[:][:] = freestream.v;
    p[:][:] = freestream.p;
  
  }

  Q[:][:][0] = rho[:][:];
  Q[:][:][1] = rho[:][:]*u[:][:];
  Q[:][:][2] = rho[:][:]*v[:][:];
  Q[:][:][3] = p[:][:]/(gamma-1) + 0.5*rho[:][:]*(u[:][:]*u[:][:] + v[:][:]*v[:][:]);

}

#endif
