%module api
%{
#include "api.h"
%}
int speed(int ni, int nj, float fsmach, float alpha, double tol, bool iread, int integrator);
