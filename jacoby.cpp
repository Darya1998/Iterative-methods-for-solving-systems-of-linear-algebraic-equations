#include "jacoby.h"
#include "convinient_system.h"
#include "iter_solution.h"

using namespace std;




std::vector<std::vector<double>> convinient_matrix_jacoby (std::vector<std::vector<double>> &matrix, vector<double> &changed_vector_jacoby, double &norm_jacobyC){
    //МАТРИЦА С, ВЫДЕЛЯЕМ ПАМЯТЬ
    std::vector<std::vector<double>> result_convinient_matrix_jacoby(matrix.size(), vector<double> (matrix[0].size() - 1));

    //ПРИВОДИМ ПЕРВОНАЧАЛЬНУЮ МАТРИЦУ К УДОБНОМУ ВИДУ(МЕТОД ЯКОБИ)
    for (int i = 0; i < matrix.size(); i++ ){
        for (int j = 1 + i; j < matrix.size(); j ++){
            vector<double> temp_vector;
            //ПЕРЕСТАНОВКА СТРОК(ЧАСТИЧНЫЙ ВЫБОР ГЛАВНОГО ЭЛЕМЕНТА)
            if (fabs(matrix[j][i]) > fabs(matrix[i][i])){
                for (int k = 0; k < matrix[0].size(); k++){
                    temp_vector.push_back(matrix[j][k]);
                }

                for (int n = 0; n < matrix[0].size(); n++){
                    matrix[j][n] = matrix[i][n];
                    matrix[i][n] = temp_vector[n];
                }
            }
        }

        for (int k = 0; k < matrix[0].size() - 1; k ++){
            result_convinient_matrix_jacoby[i][k] = -matrix[i][k]/matrix[i][i];
            if(k == i){
                result_convinient_matrix_jacoby[i][i] = 0;
            }

        }

        //МЕНЯЕМ ВЕКТОР ПРАВОЙ ЧАСТИ
        changed_vector_jacoby.resize(matrix.size());
        changed_vector_jacoby[i] = matrix[i][matrix[0].size() - 1]/matrix[i][i];

    }

    //ВЫВОД ПОЛУЧЕННОЙ МАТРИЦЫ
    for (const auto &v:result_convinient_matrix_jacoby){
        for (const auto &n:v){
            std::cout << left << setw(15) << setprecision(6) << fixed << n << "\t";
        }
        cout << endl;
    }
    std::cout << std::endl;

    //ВЫВОД ПОЛУЧЕННОГО ВЕКТРА ПРАВОЙ ЧАСТИ
    cout << "Измененный вектор правой части" << endl;
    // for (int i = 0; i < changed_vector_jacoby.size(); i ++){
    //     cout << changed_vector_jacoby[i] << "   ";
    // }

    //НОРМА ПОЛУЧЕННОЙ МАТРИЦЫ
    norm_jacobyC = norm_matrix(result_convinient_matrix_jacoby);

    return result_convinient_matrix_jacoby;
}



vector<double> jacoby_solution(std::vector<std::vector<double>> &matrix, vector <double> &changed_vector, double &norm_jacobyC, bool &diverges){

vector<double> solution_jacoby = iter_solution(matrix, changed_vector,norm_jacobyC, diverges);



return solution_jacoby;

}