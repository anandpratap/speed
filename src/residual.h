#ifndef _INCL_RESIDUAL
#define _INCL_RESIDUAL
#include "bc.h"
#include "utils.h"
#include "recon.h"
#include "flux.h"
#include <cmath>
#include <algorithm>
#include <iostream>
#include <cilk/cilk.h>

// Confession: the default abs() function returns only integer, used <cmath> and std::abs()
//             wasted a day because of this stupid function

void residual(int ni, int nj, double Q[ni-1][nj-1][4],			\
	      double neta_x[ni-1][nj], double neta_y[ni-1][nj],		\
	      double nxi_x[ni][nj-1], double nxi_y[ni][nj-1],		\
	      double res[ni-1][nj-1][4], double vol[ni-1][nj-1],	\
	      double ds_eta[ni-1][nj-1], double ds_xi[ni-1][nj-1],	\
	      double dt[ni-1][nj-1],struct state freestream,		\
	      double gamma=1.4){

  int nip = ni + 1;
  int njp = nj + 1;
  int nim = ni - 1;
  int njm = nj - 1;
  int order = 2;
  
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
 
  grad_xi(ni, nj, rho, u, v, p, rlft_xi, ulft_xi, vlft_xi, plft_xi, rrht_xi, urht_xi, vrht_xi, prht_xi, order);

#pragma omp parallel for
  for(int i = 0; i < ni; i++) {
    for(int j = 0; j < njm; j++) {
      roeflux(nxi_x[i][j], nxi_y[i][j], rlft_xi[i][j], ulft_xi[i][j], vlft_xi[i][j], plft_xi[i][j], \
	rrht_xi[i][j], urht_xi[i][j], vrht_xi[i][j], prht_xi[i][j], gamma, flux_xi[i][j]);
    }
  }
  
  res[0:nim][0:njm][0:4] = res[0:nim][0:njm][0:4] - (flux_xi[1:nim][0:njm][0:4] - flux_xi[0:nim][0:njm][0:4]);
  
  double rlft_eta[nim][nj], ulft_eta[nim][nj], vlft_eta[nim][nj], plft_eta[nim][nj];
  double rrht_eta[nim][nj], urht_eta[nim][nj], vrht_eta[nim][nj], prht_eta[nim][nj];
  double flux_eta[nim][nj][4];
  
  grad_eta(ni, nj, rho, u, v, p, rlft_eta, ulft_eta, vlft_eta, plft_eta, rrht_eta, urht_eta, vrht_eta, prht_eta, order);
  
#pragma omp parallel for
  for(int i = 0; i < nim; i++) {
  for(int j = 0; j < nj; j++) {
  roeflux(neta_x[i][j], neta_y[i][j], rlft_eta[i][j], ulft_eta[i][j], vlft_eta[i][j], plft_eta[i][j], \
    rrht_eta[i][j], urht_eta[i][j], vrht_eta[i][j], prht_eta[i][j], gamma, flux_eta[i][j]);
}
}

  res[0:nim][0:njm][0:4] = res[0:nim][0:njm][0:4] - (flux_eta[0:nim][1:njm][0:4] - flux_eta[0:nim][0:njm][0:4]);

  
}

#endif
