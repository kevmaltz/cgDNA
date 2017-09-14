#ifndef _Main_h_
#define _Main_h_

#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <cilk/cilk.h>
#include <cilk/cilk_api.h>
#include <cilk/reducer_opadd.h>
#include <mkl.h>
using namespace std;

#include "Vertex.h"
#include "Utility.h"
#include "Constants.h"


#define CONCENTRATION(Nparticles, BOXL) ((((float)Nparticles / Na) / ((BOXL * BOXL * BOXL) * LperA3)) * nMperM)
#define BOXSIZEFORnMCONC(nMCONC) pow((nMperM * (1.0 / Na) / (nMCONC * LperA3)), 1./3.)


#endif
