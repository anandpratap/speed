#ifndef _INCL_RECON
#define _INCL_RECON
#include "mkl.h"
// TEST STATUS: Not tested, simple enough functions


void first_order_xi(int ni, int nj, double q[ni+1][nj+1], double ql[ni][nj-1], double qr[ni][nj-1]);
void first_order_eta(int ni, int nj, double q[ni+1][nj+1], double ql[ni-1][nj], double qr[ni-1][nj]);



void second_order_xi(int ni, int nj, double q[ni+1][nj+1], double ql[ni][nj-1], double qr[ni][nj-1]);
void second_order_eta(int ni, int nj, double q[ni+1][nj+1], double ql[ni-1][nj], double qr[ni-1][nj]);

void grad_xi(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],\
	     double rlft[ni][nj-1], double ulft[ni][nj-1], double vlft[ni][nj-1], double plft[ni][nj-1], \
	     double rrht[ni][nj-1], double urht[ni][nj-1], double vrht[ni][nj-1], double prht[ni][nj-1], int order);

void grad_eta(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],	\
	      double rlft[ni-1][nj], double ulft[ni-1][nj], double vlft[ni-1][nj], double plft[ni-1][nj], \
	      double rrht[ni-1][nj], double urht[ni-1][nj], double vrht[ni-1][nj], double prht[ni-1][nj], int order);


#endif

