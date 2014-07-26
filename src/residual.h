#ifndef _INCL_RESIDUAL
#define _INCL_RESIDUAL
#include "bc.h"
#include "utils.h"
#include "recon.h"
#include "flux.h"
#include <cmath>
#include <algorithm>
#include <iostream>
// Confession: the default abs() function returns only integer, used <cmath> and std::abs()
//             wasted a day because of this stupid function

void residual(int ni, int nj, double Q[ni-1][nj-1][4],			\
	      double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	      double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	      double res[ni-1][nj-1][4], double vol[ni-1][nj-1], double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1], double dt[ni-1][nj-1],struct state freestream, \
	      double gamma=1.4){

  int nip = ni + 1;
  int njp = nj + 1;
  int nim = ni - 1;
  int njm = nj - 1;

  
  res[0:nim][0:njm][0:4] = 0.0;
  double rho[nip][njp], u[nip][njp], v[nip][njp], p[nip][njp];

  bc(ni, nj, Q, rho, u, v, p, neta_x, neta_y, freestream, gamma);
  
  double c[nim][njm];
  c[:][:] = sqrt(gamma*p[1:nim][1:njm]/rho[1:nim][1:njm]) + sqrt(pow(u[1:nim][1:njm],2) + pow(v[1:nim][1:njm],2));
  c[:][:] *= (ds_eta[:][:] + ds_xi[:][:]);
  dt[:][:] = vol[:][:]/c[:][:];
  
  double rlft_xi[ni][njm], ulft_xi[ni][njm], vlft_xi[ni][njm], plft_xi[ni][njm];
  double rrht_xi[ni][njm], urht_xi[ni][njm], vrht_xi[ni][njm], prht_xi[ni][njm];
  double flux_xi[ni][njm][4];
 
  grad_xi(ni, nj, rho, u, v, p, rlft_xi, ulft_xi, vlft_xi, plft_xi, rrht_xi, urht_xi, vrht_xi, prht_xi);
  roeflux(nxi_x[:][:], nxi_y[:][:], rlft_xi[:][:], ulft_xi[:][:], vlft_xi[:][:], plft_xi[:][:],	\
	  rrht_xi[:][:], urht_xi[:][:], vrht_xi[:][:], prht_xi[:][:], gamma, flux_xi[:][:]);

  res[0:nim][0:njm][0:4] = res[0:nim][0:njm][0:4] - (flux_xi[1:nim][0:njm][0:4] - flux_xi[0:nim][0:njm][0:4]);

  double rlft_eta[nim][nj], ulft_eta[nim][nj], vlft_eta[nim][nj], plft_eta[nim][nj];
  double rrht_eta[nim][nj], urht_eta[nim][nj], vrht_eta[nim][nj], prht_eta[nim][nj];
  double flux_eta[nim][nj][4];

  grad_eta(ni, nj, rho, u, v, p, rlft_eta, ulft_eta, vlft_eta, plft_eta, rrht_eta, urht_eta, vrht_eta, prht_eta);
  roeflux(neta_x[:][:], neta_y[:][:], rlft_eta[:][:], ulft_eta[:][:], vlft_eta[:][:], plft_eta[:][:], \
  	  rrht_eta[:][:], urht_eta[:][:], vrht_eta[:][:], prht_eta[:][:], gamma, flux_eta[:][:]);
  
 
  res[0:nim][0:njm][0:4] = res[0:nim][0:njm][0:4] - (flux_eta[0:nim][1:njm][0:4] - flux_eta[0:nim][0:njm][0:4]);

  
}

#endif
