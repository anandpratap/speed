#ifndef _INCL_RECON
#define _INCL_RECON
#include <cmath>
// TEST STATUS: Not tested, simple enough functions


void first_order_xi(int ni, int nj, double q[ni+1][nj+1], double ql[ni][nj-1], double qr[ni][nj-1]){
  int njm = nj-1;
  ql[0:ni][0:njm] = q[0:ni][1:njm];
  qr[0:ni][0:njm] = q[1:ni][1:njm];
}


void first_order_eta(int ni, int nj, double q[ni+1][nj+1], double ql[ni-1][nj], double qr[ni-1][nj]){
  int nim = ni-1;
  ql[0:nim][0:nj] = q[1:nim][0:nj];
  qr[0:nim][0:nj] = q[1:nim][1:nj];
}



void second_order_xi(int ni, int nj, double q[ni+1][nj+1], double ql[ni][nj-1], double qr[ni][nj-1]){
  int njm = nj-1;
  ql[0:ni][0:njm] = q[0:ni][1:njm];
  qr[0:ni][0:njm] = q[1:ni][1:njm];
  
  int nim = ni-1;
  double thm = 2.0/3.0;
  double thp = 4.0/3.0;
  double eps = pow(10.0/nim, 3);
  double f2[ni][njm], a1[nim][njm], a2[nim][njm], f3qt[nim][njm];
  f2[:][:] = q[1:ni][1:njm] - q[0:ni][1:njm];
  a1[:][:] = 3.0*f2[1:nim][:]*f2[0:nim][:];
  a2[:][:] = 2*pow(f2[1:nim][:] - f2[0:nim][:],2) + a1[:][:];
  f3qt[:][:] = 0.25*(a1[:][:] + eps)/(a2[:][:] + eps);
  ql[1:nim][:] = ql[1:nim][:] + f3qt[:][:]*(thm*f2[0:nim][:] + thp*f2[1:nim][:]);
  qr[0:nim][:] = qr[0:nim][:] - f3qt[:][:]*(thp*f2[0:nim][:] + thm*f2[1:nim][:]);
}


void second_order_eta(int ni, int nj, double q[ni+1][nj+1], double ql[ni-1][nj], double qr[ni-1][nj]){
  int nim = ni-1;
  ql[0:nim][0:nj] = q[1:nim][0:nj];
  qr[0:nim][0:nj] = q[1:nim][1:nj];

  int njm = nj-1;
  double thm = 2.0/3.0;
  double thp = 4.0/3.0;
  double eps = pow(10.0/njm, 3);
  double f2[nim][nj], a1[nim][njm], a2[nim][njm], f3qt[nim][njm];
  f2[:][:] = q[1:nim][1:nj] - q[1:nim][0:nj];
  a1[:][:] = 3.0*f2[:][1:njm]*f2[:][0:njm];
  a2[:][:] = 2*pow(f2[:][1:njm] - f2[:][0:njm],2) + a1[:][:];
  f3qt[:][:] = 0.25*(a1[:][:] + eps)/(a2[:][:] + eps);
  ql[:][1:njm] = ql[:][1:njm] + f3qt[:][:]*(thm*f2[:][0:njm] + thp*f2[:][1:njm]);
  qr[:][0:njm] = qr[:][0:njm] - f3qt[:][:]*(thp*f2[:][0:njm] + thm*f2[:][1:njm]);


}

void grad_xi(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],\
	     double rlft[ni][nj-1], double ulft[ni][nj-1], double vlft[ni][nj-1], double plft[ni][nj-1], \
	     double rrht[ni][nj-1], double urht[ni][nj-1], double vrht[ni][nj-1], double prht[ni][nj-1], int order = 2){

  if(order == 1){
    first_order_xi(ni, nj, rho, rlft, rrht);
    first_order_xi(ni, nj, u, ulft, urht);
    first_order_xi(ni, nj, v, vlft, vrht);
    first_order_xi(ni, nj, p, plft, prht);
  }
  else if(order == 2){
    second_order_xi(ni, nj, rho, rlft, rrht);
    second_order_xi(ni, nj, u, ulft, urht);
    second_order_xi(ni, nj, v, vlft, vrht);
    second_order_xi(ni, nj, p, plft, prht);
  }
  else{
    printf("order not implemented");
    exit(-1);
  }
}


void grad_eta(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],	\
	      double rlft[ni-1][nj], double ulft[ni-1][nj], double vlft[ni-1][nj], double plft[ni-1][nj], \
	      double rrht[ni-1][nj], double urht[ni-1][nj], double vrht[ni-1][nj], double prht[ni-1][nj], int order = 2){

  if(order == 1){
    first_order_eta(ni, nj, rho, rlft, rrht);
    first_order_eta(ni, nj, u, ulft, urht);
    first_order_eta(ni, nj, v, vlft, vrht);
    first_order_eta(ni, nj, p, plft, prht);
  }
  else if(order == 2){
    second_order_eta(ni, nj, rho, rlft, rrht);
    second_order_eta(ni, nj, u, ulft, urht);
    second_order_eta(ni, nj, v, vlft, vrht);
    second_order_eta(ni, nj, p, plft, prht);
  }
  else{
    printf("order not implemented");
    exit(-1);
  }
}


#endif

