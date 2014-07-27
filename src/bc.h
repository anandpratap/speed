#ifndef _INCL_BC
#define _INCL_BC

#include "utils.h"
#include <cmath>

// TEST STATUS: Not tested, but should work fine
void bc(int ni, int nj, double Q[ni-1][nj-1][4],			\
	double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1], \
	double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	struct state freestream, float gamma=1.4){
  
  int nim = ni - 1;
  int njm = nj - 1;

  primvars(Q[:][:], gamma, &rho[1:nim][1:njm], &u[1:nim][1:njm], &v[1:nim][1:njm], &p[1:nim][1:njm]);
  
  
  double rho_inf = freestream.rho;
  double u_inf = freestream.u;
  double v_inf = freestream.v;
  double p_inf = freestream.p;
  


  rho[0][:] = rho_inf;
  u[0][:] = u_inf;
  v[0][:] = v_inf;
  p[0][:] = p_inf;
  
  rho[ni][:] = rho_inf;
  u[ni][:] = u_inf;
  v[ni][:] = v_inf;
  p[ni][:] = p_inf;

  rho[:][nj] = rho_inf;
  u[:][nj] = u_inf;
  v[:][nj] = v_inf;
  p[:][nj] = p_inf;

  int j1 =41;
  int nb = 200;


  double un[nb];
  double ds[nb];
  ds[:] =pow(neta_x[j1-1:nb][0], 2) + pow(neta_y[j1-1:nb][0], 2);

  p[j1:nb][0] = 1.5*p[j1:nb][1] - 0.5*p[j1:nb][2];
  rho[j1:nb][0] = 1.5*rho[j1:nb][1] - 0.5*rho[j1:nb][2];

  un[:] = ((1.5*u[j1:nb][1] - 0.5*u[j1:nb][2])*neta_x[j1-1:nb][0] + (1.5*v[j1:nb][1] - 0.5*v[j1:nb][2])*neta_y[j1-1:nb][0]);
  u[j1:nb][0] = 1.5*u[j1:nb][1] - 0.5*u[j1:nb][2] - 2*un[:]*neta_x[j1-1:nb][0]/ds[:];
  v[j1:nb][0] = 1.5*v[j1:nb][1] - 0.5*v[j1:nb][2] - 2*un[:]*neta_y[j1-1:nb][0]/ds[:];

  rho[1:j1-1][0] = rho[nim:j1-1:-1][1];
  u[1:j1-1][0] = u[nim:j1-1:-1][1];
  v[1:j1-1][0] = v[nim:j1-1:-1][1];
  p[1:j1-1][0] = p[nim:j1-1:-1][1];

  rho[nim:j1-1:-1][0] = rho[1:j1-1][1];
  u[nim:j1-1:-1][0] = u[1:j1-1][1];
  v[nim:j1-1:-1][0] = v[1:j1-1][1];
  p[nim:j1-1:-1][0] = p[1:j1-1][1];


}

#endif
