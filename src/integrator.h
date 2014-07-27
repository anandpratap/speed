#ifndef _INCL_INTEGRATOR
#define _INCL_INTEGRATOR
#include "residual.h"

void euler(int ni, int nj, double Q[ni-1][nj-1][4],			\
	   double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	   double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	   double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], \
	   struct state freestream, double* res_rho, float gamma = 1.4){
  
  int nim = ni - 1;
  int njm = nj - 1;
  double res[nim][njm][4];
  double dt[nim][njm];
  
  residual(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, res, vol, ds_eta, ds_xi, dt, freestream, gamma);
  for(int i=0; i< 4; i++)
    Q[:][:][i] = Q[:][:][i] + res[:][:][i]/vol[:][:]*(dt[:][:])*.5;
  

  *res_rho = sqrt(__sec_reduce_add(pow(res[:][:][0],2)));

  
}

void jst(int ni, int nj, double Q[ni-1][nj-1][4],			\
	 double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	 double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	 double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], \
	 struct state freestream, double* res_rho, float gamma = 1.4){
  
  int nim = ni - 1;
  int njm = nj - 1;
  double res[nim][njm][4];
  double dt[nim][njm];
  double dt_orig[nim][njm];
  int order = 4;
  *res_rho = 0.0;
  for(int n=0; n< order; n++){
    residual(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, res, vol, ds_eta, ds_xi, dt, freestream, gamma);
    if(n==0){
      dt_orig[:][:] = dt[:][:];
    }
    for(int i=0; i< 4; i++)
      Q[:][:][i] = Q[:][:][i] + res[:][:][i]/vol[:][:]*dt_orig[:][:]/(order-n)*2.0;
    
    *res_rho += sqrt(__sec_reduce_add(pow(res[:][:][0],2)));
  }


}






#endif
