#ifndef _CONVINIENT_SYSTEM_
#define _CONVINIENT_SYSTEM_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>
#include <math.h>


using namespace std;


std::vector<std::vector<double>> convinient_matrix(std::vector<std::vector<double>> &matrix, double &temp_iter_parametr, std::vector<double> &vectorY, double &normC);

double norm_matrix(std::vector<std::vector<double>> &matrix);

double norm_vector_right_part(vector<double> &vectory);

std::vector<double> free_term_finding(double temp_iter_parametr, std::vector<std::vector<double>> &matrix);



#endif