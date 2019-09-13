#ifndef _APRIOR_
#define _APRIOR_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>
#include "eps.h"



using namespace std;

int aprior_amount_steps(double &norm_C, double &norm_vector);
double aprior_ERROR(int k, double &normC, double &norm_vector);

#endif