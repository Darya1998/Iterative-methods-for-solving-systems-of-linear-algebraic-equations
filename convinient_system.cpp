#include "convinient_system.h"

using namespace std;

//НОРМА С КУБИЧЕСКАЯ
double norm_matrix(std::vector<std::vector<double>> &matrix){
    double max_row = 0;
     
    for (int i = 0; i < matrix.size(); i++){
        double temp_max_row = 0;
        for (int j = 0; j < matrix.size(); j ++){
            temp_max_row += fabs(matrix[i][j]);
        }

        if (temp_max_row > max_row){
            max_row = temp_max_row;
        }
    }

    return max_row;
}


//ФУНКЦИЯ НАХОЖДЕНИЯ ВЕКОРА Y, КОТОРЫЙ НАХОДИТСЯ ПУТЕ УМНОЖЕНИЯ ТАУ НА ВЕКТОР ПРАВОЙ ЧАСТИ
std::vector<double> free_term_finding(double temp_iter_parametr, std::vector<std::vector<double>> &matrix){
    int rows = matrix.size();
    int columns = matrix[0].size() - 1;

    std::vector<double> free_term(rows);

    for (int i = 0; i < rows; i ++){
        free_term[i] = temp_iter_parametr * matrix[i][columns];
    }
    return free_term;

}

//ФУНКЦИЯ НАХОЖДЕНИЯ НОРМЫ ВЕКТОРА ПРАВОЙ ЧАСТИ

double norm_vector_right_part(vector<double> &vectory){
    double max = 0;
    for (int i = 0; i < vectory.size(); i ++){
        if (fabs(vectory[i]) > max){
            max = fabs(vectory[i])  ;
        }
    }

    return max;
}


std::vector<std::vector<double>> convinient_matrix(std::vector<std::vector<double>> &matrix, double &temp_iter_parametr, std::vector<double> &vectorY, double &normC){

    double iter_parametr = 1;
    
    
    std::vector<std::vector<double>> result_convinient_matrix(matrix.size(), vector<double> (matrix[0].size() - 1));


    //Выполняем цикл пока норма матрицы С не станет меньше 1
    // int t = 0;
    // while(normC >= 1){
    //     t++;
    //     if (t > 100){
    //         diverges = true;
    //         cout << "Метод расходится" << endl;
    //         return result_convinient_matrix;
    //     }
    //     for (int i = 0; i < matrix.size(); i++){
    //         for(int j = 0; j < matrix[0].size() - 1; j++){
    //             result_convinient_matrix[i][j] =  -(iter_parametr * matrix[i][j]);
    //             if (i == j){
    //                 result_convinient_matrix[i][j]++;  //Вычитаем единичную матрицу
    //             }

    //         }
    //     }
        
    //     //НОРМА МАТРИЦЫ, ПРИВЕДЕННОЙ К УДОБНОМУ ВИДУ(МЕТОД ПРОСТОЙ ИТЕРАЦИИ)
    //     normC= norm_matrix(result_convinient_matrix);
    //     temp_iter_parametr = iter_parametr;
    //     iter_parametr = iter_parametr * 1/5;
    // }

    int t = 0;
    // while (normC >= 1){
    //     t++;
    //     if(t > 20){
    //         break;
    //     }
    //     for (int i = 0; i < matrix.size(); i++){
    //         for(int j = 0; j < matrix[0].size() - 1; j++){
    //             result_convinient_matrix[i][j] =  -(iter_parametr * matrix[i][j]);
    //             if (i == j){
    //                 result_convinient_matrix[i][j]++;  //Вычитаем единичную матрицу
    //             }

    //         }
    //     }

    //     //НОРМА МАТРИЦЫ, ПРИВЕДЕННОЙ К УДОБНОМУ ВИДУ(МЕТОД ПРОСТОЙ ИТЕРАЦИИ)
    //     normC= norm_matrix(result_convinient_matrix);
    //     temp_iter_parametr = iter_parametr;
    //     iter_parametr = iter_parametr * 1/9;

    // }
    iter_parametr = 0.06;

    cout << "ПОЛУЧЕННАЯ МАТРИЦА" << endl;
    for (const auto &v:result_convinient_matrix){
        for (const auto &n: v){
            cout << n << "   ";
        }
        cout <<  endl;
    }

    cout <<  endl;


    //cout << "Итерационный параметр "<< iter_parametr << endl;


    //НАХОЖДЕНИЕ ВЕКОРА Y, КОТОРЫЙ НАХОДИТСЯ ПУТЕМ УМНОЖЕНИЯ ТАУ НА ВЕКТОР ПРАВОЙ ЧАСТИ
    vectorY = free_term_finding(temp_iter_parametr, matrix);
    cout << "вектор игрик" << endl;
    for (const auto &n: vectorY){
        cout << n << endl;
    }    

    cout << "\nНорма матрицы С, приведенной к удобному виду. Метод простой итерации = "  << normC << endl;
    return result_convinient_matrix;

}


