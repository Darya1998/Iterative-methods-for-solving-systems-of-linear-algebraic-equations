#ifndef _ZEYDEL_RELAXATION_
#define _ZEYDEL_RELAXATION_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


using namespace std;

double norm_zeidel(vector<vector<double>> &matrix, double w);
std::vector<std::vector<double>> zeydel_relaxation_matrix(std::vector<std::vector<double>> &matrix, vector<double> &changed_vector_zeydel, double &norm_zeydelC);
vector<double> zeydel_relax_solution(double &parametr, std::vector<std::vector<double>> &matrix_zeydel, vector<double> &changed_vector_zeydel, double norm_B, double &parametr_apost);
double norm_up_triangle(std::vector<std::vector<double>> &matrix);

#endif