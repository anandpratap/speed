#ifndef _INCL_FORCE
#define _INCL_FORCE
#include "utils.h"
void force(int ni, int nj, double Q[ni-1][nj-1][4],			\
	   double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	   double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	   double xc[ni-1][nj-1], double yc[ni-1][nj-1],		\
	   struct state freestream, double gamma=1.4){

  int nim = ni - 1;
  int njm = nj - 1;
  int j1 = 40;
  int nb = 200;
  
  
  double p_inf = freestream.p;
  double rho_inf = freestream.rho;
  double u_inf_2 = freestream.u*freestream.u + freestream.v*freestream.v;
  
  double rho[nim][njm], u[nim][njm], v[nim][njm], p[nim][njm];
  primvars(Q[:][:], gamma, &rho[:][:], &u[:][:], &v[:][:], &p[:][:]);
  
  
  double cp[nb], pw[nb], xw[nb];
  pw[:] = 1.5*p[j1:nb][0] - 0.5*p[j1:nb][1];
  xw[:] = 1.5*xc[j1:nb][0] - 0.5*xc[j1:nb][1];
  double q_inf = 0.5*rho_inf*u_inf_2;
  cp[:] = (pw[:] - p_inf)/q_inf;
  
  // write cp
  std::ofstream outfile;
  outfile.open("cp.dat");
  char buffer [500];
  for(int i=0; i<nb; i++){
    sprintf(buffer, "%8.14E %8.14E\n", xw[i], cp[i]);
    outfile<<buffer;
  }
  outfile.close();
  printf("Cp dumped..\n");
  
  // calc Fx and Fy

  double Fx, Fy;
  Fx = -__sec_reduce_add(cp[:]*neta_x[j1:nb][0]);
  Fy = -__sec_reduce_add(cp[:]*neta_y[j1:nb][0]);

  double alpha = freestream.alpha;
  double Cl, Cd;
  Cl = Fy*cos(alpha) - Fx*sin(alpha);
  Cd = Fx*cos(alpha) + Fy*sin(alpha);

  printf("Cl: %f Cd: %f\n", Cl, Cd);
}
	   

#endif
