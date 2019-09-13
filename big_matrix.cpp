#include "big_matrix.h"
#include "iter_solution.h"
#include "zeydel_relaxation.h"
#include "norm_error.h"

#include "eps.h"


std::vector<std::vector<double>> creation_big_matrix(int N){
    std::vector<std::vector<double>> tgreediagonal(4, vector<double> (N));

    int i = 0;
    for (int j = 0; j < tgreediagonal[0].size(); j++){
        tgreediagonal[i][j] = 1;
        tgreediagonal[i + 1][j] = 4;
        tgreediagonal[i + 2][j] = 1;
        tgreediagonal[i + 3][j] = 10 - 2 * ((j+1)%2);
    }

    tgreediagonal[0][N - 1] = 0;
    tgreediagonal[2][0] = 0;
    tgreediagonal[i + 3][0] = 6;
    tgreediagonal[i + 3][N - 1] = 9 - 3 * (N%2);

    return tgreediagonal;

}

std::vector<std::vector<double>> convinient_big_matrix(std::vector<std::vector<double>> init_big_matrix){
    for (int i = 0; i < init_big_matrix.size(); i ++){
        for (int j = 0; j < init_big_matrix[0].size(); j ++){
            //ПРИВЕДЕНИЕ ТРЕХДИАГОНАЛЬНОЙ МАТРИЦЫ К УДОБНОМУ ВИДУ
            if (i != 1){
                init_big_matrix[i][j] = pow(-1, i + 1) * init_big_matrix[i][j]/init_big_matrix[1][j];
            }
        }

    }
    //ОБНУЛЯЕМ ЭЛЕМЕНТЫ НА ГЛАВНОЙ ДИАГОНАЛИ
    for (int j = 0; j < init_big_matrix[0].size(); j ++){
        init_big_matrix[1][j] = 0;
    }
    return init_big_matrix;
}


double norm_b(std::vector<std::vector<double>> b_matrix ){
    double max = fabs(b_matrix[0][1]) + fabs(b_matrix[2][1]);
    return max;

}

//СОЗДАДИМ МАТРИЦУ 200 НА 200
std::vector<std::vector<double>> make_big_matrix(int N){
    std::vector<std::vector<double>> matr_big(N, vector<double> (N));
    for (int i = 0; i < N; i ++){
        matr_big[i][i] = 4;
        if(i < N -1){
            matr_big[i][i + 1] = 1;
            matr_big[i+1][i] = 1;

        }
        
    }
    return matr_big;
}





//НАХОЖДЕНИЕ РЕШЕНИЯ  

vector<double> solution_big_matrix(std::vector<std::vector<double>> &big_matrix, double norm_big_matrix, double parametr_big_matix){
   double Epsilon2 = (1 - norm_big_matrix)/0.25 * EPSILON;; 

    // if (norm_big_matrix <=1/2){
    //     Epsilon2 = EPSILON;
    // }
    // else{
    //     Epsilon2 = (1 - norm_big_matrix)/norm_big_matrix * EPSILON;
    // }

    

    double norm_difference_big_matrix = 1;


    //ВЫЛЕЛЯЕМ ПАМЯТЬ ПОД ВЕКТОРА РЕШЕНИЙ(ТЕКУЩИЙ И ПРЕДЫДУЩИЙ)
    vector<double> init_solution_big_matrix(big_matrix[0].size());
    vector<double> new_solution_big_matrix(big_matrix[0].size());


    //ПУСТЬ НАЧАЛЬНЫМ ПРИБЛЕЖНИЕМ БУДЕТ НУЛЕВОЙ ВЕКТОР
    for (int i = 0; i < big_matrix[0].size(); i ++){
        init_solution_big_matrix[i] = 0;
        new_solution_big_matrix[i] = 0;
    }

    //РАЗНОСТЬ X^N И X^(N-1) РЕШЕНИЙ
    std::vector<double> vector_difference_big_matr(big_matrix[0].size());

    int amount_iter_big_matrix = 0;

    while(norm_difference_big_matrix >= Epsilon2){

        amount_iter_big_matrix++;

        //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
        for (int i = 0; i < big_matrix[0].size(); i ++){
            init_solution_big_matrix[i] = new_solution_big_matrix[i];
            new_solution_big_matrix[i] = 0;
        }

        for (int i = 0; i < big_matrix[0].size(); i ++){
            //new_solution[i] = (1 - parametr) * init_solution[i] + parametr * product_B1_xnew + parametr * product_B2_xold + parametr * changed_vector_zeydel[i];
            new_solution_big_matrix[i] = (1 - parametr_big_matix) * init_solution_big_matrix[i] + parametr_big_matix * big_matrix[2][i] * new_solution_big_matrix[i - 1] + parametr_big_matix * big_matrix[0][i] * init_solution_big_matrix[i + 1]+ parametr_big_matix * big_matrix[3][i];

        }

        double l = norm_error_big_matrix(new_solution_big_matrix);
            if (l <= EPSILON){
                cout << "достииигнууууууууууутаааааааааа   " << amount_iter_big_matrix << endl;
            }




        for (int i = 0; i < big_matrix[0].size(); i++){
            vector_difference_big_matr[i] = new_solution_big_matrix[i] - init_solution_big_matrix[i];
        }

        //НОРМА ВЕКТОРА РАЗНОСТИ
        norm_difference_big_matrix = norm_vector(vector_difference_big_matr);

    }

    cout << "Количество итераций. Большая матрица =  " << amount_iter_big_matrix << endl;
    return new_solution_big_matrix;


}
