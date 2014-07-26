#ifndef _INCL_SOLVER
#define _INCL_SOLVER
#include "integrator.h"
#include "io.h"

void print_stuff(double res_rho, int iteration){
  printf("res_rho_l2: %8.3E, iteration: %d\n",res_rho, iteration);
}

void solver(int ni, int nj, double Q[ni-1][nj-1][4],			\
	    double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	    double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	    double vol[ni-1][nj-1], double xc[ni-1][nj-1], double yc[ni-1][nj-1], \
	    double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1],	\
	    struct state freestream, double tf, int integrator,		\
	    double gamma = 1.4, bool steadystate=true){
  
  
  double res_rho = 1e1;
  int iteration = 1;
  while(res_rho > tf){
    if(integrator == 0){
      euler(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, vol, ds_eta, ds_xi, freestream, &res_rho, gamma);
    }
    else if(integrator == 1){
      jst(ni, nj, Q, neta_x, neta_y, nxi_x, nxi_y, vol, ds_eta, ds_xi, freestream, &res_rho, gamma);
    }
    else{
      printf("Integrator not defined.\n");
      exit(-1);
    }
    
    if(iteration%100==0)
      print_stuff(res_rho, iteration);
    if(iteration%1000==0)
      writedata(ni, nj, Q, xc, yc);
    
    iteration += 1;
  }
  
}

#endif
