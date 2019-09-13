#ifndef _BIG_MATRIX_
#define _BIG_MATRIX_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


using namespace std;



std::vector<std::vector<double>> creation_big_matrix(int N);
std::vector<std::vector<double>> convinient_big_matrix(std::vector<std::vector<double>> init_big_matrix);
std::vector<std::vector<double>> make_big_matrix(int N);
double norm_b(std::vector<std::vector<double>> b_matrix );
vector<double> solution_big_matrix(std::vector<std::vector<double>> &big_matrix, double norm_big_matrix, double parametr_big_matix);





#endif