#ifndef _INCL_FLUX
#define _INCL_FLUX
#include "mkl.h"
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
				 float gamma, double f[4]);

#endif
