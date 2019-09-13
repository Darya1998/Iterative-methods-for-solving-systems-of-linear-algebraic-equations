#include "norm_error.h"

double norm_error(std::vector<double> &solution){
    //ДЛЯ ПЕРВОГО ТЕСТА
    //vector<double> precise_sol = {5, -7, 12, 4};

    //ДЛЯ ВТОРОГО ТЕСТА
    vector<double> precise_sol = {10, -10, 12, 4};

    // ДЛЯ 13 ТЕСТА
    //vector<double> precise_sol = {-7, 7, 2, -6};

    // ДЛЯ 3 ТЕСТА
    //vector<double> precise_sol = {2, -5, 12, 3};


    //Найдем разницу между векторами x и x*
    double max = 0;
    cout << endl;


    vector<double> delta_x(solution.size());
    for (int i = 0; i < solution.size(); i++){
        delta_x[i] = fabs(solution[i] - precise_sol[i]);
        if (delta_x[i] > max){
            max = delta_x[i];
        }
    }

    // cout << "\nНорма погрешности" << endl;
    // cout << setprecision(9) << fixed << max << endl;

    return max;

}

double norm_error_big_matrix(std::vector<double> &solution){
    double max;

    vector<double> delta_x(solution.size());

    for (int i = 0; i < solution.size(); i++){
        delta_x[i] = fabs(solution[i] - (2 - ((i+1)%2)));
        if (delta_x[i] > max){
            max = delta_x[i];
        }
    }

    //cout << "\nНорма погрешности" << endl;
    return max;


}

