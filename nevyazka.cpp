#include "nevyazka.h"


double nevyazka(std::vector<std::vector<double>> &matrix, std::vector<double> &solution){
    std::vector<double> matr_product(matrix.size());

    for (int i = 0; i < matrix.size(); i ++){
        matr_product[i] = 0;
        for (int j = 0; j < solution.size(); j++){
            matr_product[i] += matrix[i][j] * solution[j];
        }
    }

    //Вывод правой части b*
    // cout << "\n В*" << endl;
    // for (const auto &n:matr_product){
    //     cout << n << "  ";
    // }
    // cout << endl;

    //Найдем разницу между векторами b и b*
    double max = 0;
    vector<double> delta_b(matr_product.size());
    double norm_nevyazky = 0;
    for (int i = 0; i < matr_product.size(); i++){
        delta_b[i] = fabs(matr_product[i] - matrix[i][matrix[0].size() - 1]);
        // cout << delta_b[i] << endl;
        if (delta_b[i] > max){
            max = delta_b[i];
        }
    }

    cout << "Норма невязки" << endl;
    cout << setprecision(9) << fixed << max << endl;


}

double nevyazka_big_matrix(std::vector<std::vector<double>> &matrix, std::vector<double> &solution, int N){
    int n = N;

    std::vector<double> matr_product(matrix[0].size());

    for (int i = 1; i < matrix[0].size() - 1; i ++){
        matr_product[i] = matrix[0][i] * solution[i+1] + matrix[1][i] * solution[i] + matrix[2][i] * solution[i-1];
    }
    matr_product[0] = matrix[0][0] * solution[1] + matrix[1][0] * solution[0];
    matr_product[matrix[0].size() - 1] = matrix[1][matrix[0].size() - 1] * solution[matrix[0].size() - 1] + matrix[2][matrix[0].size() - 1] * solution[matrix[0].size() - 2];

   


    //Найдем разницу между векторами b и b*
    double max = 0;
    vector<double> delta_b(matr_product.size());
    double norm_nevyazky = 0;
    for (int i = 1; i < matr_product.size() - 1; i++){
        delta_b[i] = fabs(matr_product[i] - (10 - 2*((i+1)%2)));
        // cout << delta_b[i] << endl;
        if (delta_b[i] > max){
            max = delta_b[i];
        }
    }
    // cout << "Вектор правой части"<< endl;
    // for (const auto &n:matr_product){
    //     cout << n << "   ";
    // }
    // cout << endl;

    // delta_b[0] = fabs(matr_product[0] - 6);
    cout << delta_b[0] << endl;
    // delta_b[matr_product.size()-1] = fabs(matr_product[matr_product.size()-1] - (9 - 3*(n%2)));
    cout << delta_b[matr_product.size()-1] << endl;

    if (delta_b[0] > max){
        max = delta_b[0];
    }

    if (delta_b[matr_product.size()-1] > max){
        max = delta_b[matr_product.size()-1];
    }

    return max;

}