#ifndef _INCL_FLUX
#define _INCL_FLUX
#include <cmath>
#include <stdlib.h>
#include<iostream>
#include <assert.h>
#include <typeinfo>

// nx and ny are face normal, see type double
// can make this much better!
// TEST STATUS: checked, DEFCON 3

__declspec(vector)  void roeflux(double nx, double ny,		\
				 double rlft, double ulft, double vlft, double plft, \
				 double rrht, double urht, double vrht, double prht, \
				 double gamma, double f[4]){
  double gm1 = gamma - 1.0;
  double ogm1 = 1/gm1;

  double rlfti = 1/rlft;
  double rulft = rlft*ulft;
  double rvlft = rlft*vlft;
  double uvl = 0.5*(ulft*ulft + vlft*vlft);
  double elft = plft*ogm1 + rlft*uvl;
  double hlft = (elft + plft)*rlfti;


  double rrhti = 1/rrht;
  double rurht = rrht*urht;
  double rvrht = rrht*vrht;
  double uvr = 0.5*(urht*urht + vrht*vrht);
  double erht = prht*ogm1 + rrht*uvr;
  double hrht = (erht + prht)*rrhti;
  
  double rat = sqrt(rrht*rlfti);
  double rati = 1/(rat+1);
  double rav = rat*rlft;
  double uav = (rat*urht + ulft)*rati;
  double vav = (rat*vrht + vlft)*rati;
  double hav = (rat*hrht + hlft)*rati;
  double uv = 0.5*(uav*uav + vav*vav);
  double cav = sqrt(gm1*(hav - uv));

  double aq1 = rrht - rlft;
  double aq2 = urht - ulft;
  double aq3 = vrht - vlft;
  double aq4 = prht - plft;
  
  double dr = sqrt(nx*nx + ny*ny);
  double r1 = nx/dr;
  double r2 = ny/dr;

  //assert(abs(r2) < 1e-10);
  double uu = r1*uav + r2*vav;
  double c2 = cav*cav;
  double c2i = 1/c2;
  double auu = std::abs(uu);
  double aupc = std::abs(uu + cav);
  double aumc = std::abs(uu - cav);

  double uulft = r1*ulft + r2*vlft;
  double uurht = r1*urht + r2*vrht;
  /* std::cout<<typeid(std::abs(rlft-rrht)).name()<<"\n"; */
  /* if(abs(rlft-rrht)>1e-10){ */
  /*   std::cout<<r1<<"uulft "<<vlft<<"\n"; */
  /*   std::cout<<r1<<"uurht "<<vlft<<"\n"; */
  /* } */
  double rcav = rav*cav;
  double aquu = uurht - uulft;
  double c2ih = 0.5*c2i;
  double ruuav = auu*rav;
  
  double b1, b2, b3, b4, b5, b6, b7;
  b1 = auu*(aq1 - c2i*aq4);
  b2 = c2ih*aupc*(aq4 + rcav*aquu);
  b3 = c2ih*aumc*(aq4 - rcav*aquu);
  b4 = b1 + b2 + b3;
  b5 = cav*(b2 - b3);
  b6 = ruuav*(aq2 - r1*aquu);
  b7 = ruuav*(aq3 - r2*aquu);

  aq1 = b4;
  aq2 = uav*b4 + r1*b5 + b6;
  aq3 = vav*b4 + r2*b5 + b7;
  aq4 = hav*b4 + uu*b5 + uav*b6 + vav*b7 - c2*b1*ogm1;

  double aj = 0.5*dr;
  double plar = plft + prht;
  double eplft = elft + plft;
  double eprht = erht + prht;
  f[0] = aj*(rlft*uulft + rrht*uurht - aq1);
  f[1] = aj*(rulft*uulft + rurht*uurht + r1*plar - aq2);
  f[2] = aj*(rvlft*uulft + rvrht*uurht + r2*plar - aq3);

  //  std::cout<<"roe"<<f[2]<<" "<<b7<<"\n";
  f[3] = aj*(eplft*uulft + eprht*uurht - aq4);

}

#endif
