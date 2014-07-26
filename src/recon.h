#ifndef _INCL_RECON
#define _INCL_RECON

// TEST STATUS: Not tested, simple enough functions

void first_order_xi(int ni, int nj, double q[ni+1][nj+1], double ql[ni][nj-1], double qr[ni][nj-1]){
  int njm = nj-1;
  ql[0:ni][0:njm] = q[0:ni][0:njm];
  qr[0:ni][0:njm] = q[1:ni][0:njm];
  
}

void first_order_eta(int ni, int nj, double q[ni+1][nj+1], double ql[ni-1][nj], double qr[ni-1][nj]){
  int nim = ni-1;
  ql[0:nim][0:nj] = q[0:nim][0:nj];
  qr[0:nim][0:nj] = q[0:nim][1:nj];
  
}

void grad_xi(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],\
	     double rlft[ni][nj-1], double ulft[ni][nj-1], double vlft[ni][nj-1], double plft[ni][nj-1], \
	     double rrht[ni][nj-1], double urht[ni][nj-1], double vrht[ni][nj-1], double prht[ni][nj-1]){
  
  first_order_xi(ni, nj, rho, rlft, rrht);
  first_order_xi(ni, nj, u, ulft, urht);
  first_order_xi(ni, nj, v, vlft, vrht);
  first_order_xi(ni, nj, p, plft, prht);
  
}


void grad_eta(int ni, int nj, double rho[ni+1][nj+1], double u[ni+1][nj+1], double v[ni+1][nj+1], double p[ni+1][nj+1],	\
	      double rlft[ni-1][nj], double ulft[ni-1][nj], double vlft[ni-1][nj], double plft[ni-1][nj], \
	      double rrht[ni-1][nj], double urht[ni-1][nj], double vrht[ni-1][nj], double prht[ni-1][nj]){
  
  first_order_eta(ni, nj, rho, rlft, rrht);
  first_order_eta(ni, nj, u, ulft, urht);
  first_order_eta(ni, nj, v, vlft, vrht);
  first_order_eta(ni, nj, p, plft, prht);
  
}


#endif

