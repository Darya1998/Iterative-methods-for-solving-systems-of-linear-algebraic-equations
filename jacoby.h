#ifndef _JACOBY_
#define _JACOBY_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


std::vector<std::vector<double>> convinient_matrix_jacoby (std::vector<std::vector<double>> &matrix, std::vector<double> &changed_vector_jacoby, double &norm_jacobyC);

std::vector<double> jacoby_solution(std::vector<std::vector<double>> &matrix, std::vector <double> &changed_vector, double &norm_jacobyC, bool &diverges);
#endif