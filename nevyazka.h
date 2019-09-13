#ifndef _NEVYAZKA_
#define _NEVYAZKA_

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>


using namespace std;
double nevyazka(std::vector<std::vector<double>> &matrix, std::vector<double> &solution);
double nevyazka_big_matrix(std::vector<std::vector<double>> &matrix, std::vector<double> &solution, int n);


#endif