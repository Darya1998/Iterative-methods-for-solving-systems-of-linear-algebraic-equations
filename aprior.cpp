#include "aprior.h"


//НАЙДЕМ АПРИОРНУЮ ОЦЕНКУ КОЛИЧЕСТВА ИТЕРАЦИЙ
int aprior_amount_steps(double &norm_C, double &norm_vector){
	double k = fabs(log(fabs(EPSILON - (1 - norm_C))/norm_vector)/fabs(log(norm_C)));

	// /0.1   C = 0.96875
	//        y = 3.3437

    return round(k);

}


//НАЙДЕМ АПРИОРНУЮ ОЦЕНКУ ПОГРЕШНОСТИ
double aprior_ERROR(int k, double &normC, double &norm_vector){

	double aprior_error = (pow(normC, k)/(1 - normC)) * norm_vector;
	return aprior_error;
}

