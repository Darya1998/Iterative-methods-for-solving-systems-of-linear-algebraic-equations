#ifndef _ITER_SOLUTION_
#define _ITER_SOLUTION_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>


using namespace std;

double norm_vector(vector<double> &diff_vector);
std::vector<double> iter_solution(std::vector<std::vector<double>> &matrixC, std::vector<double> &vectorY, double normC, bool &diverges);



#endif