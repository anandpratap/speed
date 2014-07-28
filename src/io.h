#ifndef _INCL_IO
#define _INCL_IO
#include <fstream>
#include <iostream>
#include <iomanip>
#include "stdio.h"
#include "utils.h"

void readgrid(int ni, int nj, double x[ni][nj], double y[ni][nj]);
void writedata(int ni, int nj, double Q[ni-1][nj-1][4], double xc[ni-1][nj-1], double yc[ni-1][nj-1]);

#endif
