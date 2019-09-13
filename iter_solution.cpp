#include "convinient_system.h"
#include "iter_solution.h"
#include "norm_error.h"

#include "eps.h"

using namespace std;


double norm_vector(vector<double> &diff_vector){
    double max = fabs(diff_vector[0]);

    for (int i = 0; i < diff_vector.size(); i++){
        if (fabs(diff_vector[i]) > max){
            max = fabs(diff_vector[i]);
        }
    }
    return max;
}

std::vector<double> iter_solution(std::vector<std::vector<double>> &matrixC, std::vector<double> &vectorY, double normC, bool &diverges){
    double epsilon1;
    if (normC <=1/2){
        epsilon1 = EPSILON;
    }
    else{
        epsilon1 = (1 - normC)/normC * EPSILON;
    }

    vector<double> init_solution(matrixC.size());
    vector<double> new_solution(matrixC.size());


    //ПУСТЬ НАЧАЛЬНЫМ ПРИБЛЕЖНИЕМ БУДЕТ НУЛЕВОЙ ВЕКТОР
    for (int i = 0; i < matrixC.size(); i ++){
        init_solution[i] = 0;
        new_solution[i] = 0;
    }

    //РАЗНОСТЬ X^N И X^(N-1) РЕШЕНИЙ
    std::vector<double> vector_difference(matrixC.size());
    //НОРМА РАЗНОСТИ X^N И X^(N-1) РЕШЕНИЙ
    double norm_difference = 1;
    double previous_norm_difference = norm_difference;
    //КОЛ-ВО ИТЕРАЦИЙ 
    int amount_iterations = 0;

    //СЧЕТЧИК
    int counter = 0;

   
    while(norm_difference >= epsilon1){

        //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
        for (int i = 0; i < matrixC.size(); i ++){
            init_solution[i] = new_solution[i];
            new_solution[i] = 0;
        }

        for (int i = 0; i < matrixC.size(); i ++){
            for (int j = 0; j < matrixC.size(); j ++){
                new_solution[i] += matrixC[i][j] * init_solution[j];
            }
        new_solution[i] += vectorY[i];   
        }

        double l = norm_error(new_solution);
        if (l <= EPSILON){
            cout << "достииигнууууууууууутаааааааааа   " << amount_iterations << endl;
        }

        //ВЕКТОР РАЗНОСТИ N-ОГО И (N-1)-ОГО РЕШЕНИЙ
        for (int i = 0; i < matrixC.size(); i++){
            vector_difference[i] = new_solution[i] - init_solution[i];
        }
        //НОРМА ВЕКТОРА РАЗНОСТИ
        norm_difference = norm_vector(vector_difference);

        if (previous_norm_difference < norm_difference){
            counter++;
        }

        //ПРОВЕРКА НА СХОДИМОСТЬ
        if (counter == 100){
            diverges = true;
            return new_solution;
        }
        previous_norm_difference = norm_difference;

        amount_iterations++;


    }
    cout << "Количество итераций = " << amount_iterations << endl; 

    //Априорная погрешность
    // double norm_y = norm_vector_right_part(vectorY);
    // int k = 0;
    // while (k <= (log(epsilon1 * (1 - normC)/(norm_y))/log(normC))){
    //     //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
    //     for (int i = 0; i < matrixC.size(); i ++){
    //         init_solution[i] = new_solution[i];
    //         new_solution[i] = 0;
    //     }

    //     for (int i = 0; i < matrixC.size(); i ++){
    //         for (int j = 0; j < matrixC.size(); j ++){
    //             new_solution[i] += matrixC[i][j] * init_solution[j];
    //         }
    //     new_solution[i] += vectorY[i];   
    //     }

    //     //ВЕКТОР РАЗНОСТИ N-ОГО И (N-1)-ОГО РЕШЕНИЙ
    //     for (int i = 0; i < matrixC.size(); i++){
    //         vector_difference[i] = new_solution[i] - init_solution[i];
    //     }
    //     //НОРМА ВЕКТОРА РАЗНОСТИ
    //     norm_difference = norm_vector(vector_difference);

    //     if (previous_norm_difference < norm_difference){
    //         counter++;
    //     }

    //     //ПРОВЕРКА НА СХОДИМОСТЬ
    //     if (counter == 100){
    //         diverges = true;
    //         return new_solution;
    //     }
    //     previous_norm_difference = norm_difference;

    //     k++;

    // }

    // cout << "Количество итераций, априорная оценка = " << k << endl;
    return new_solution;
    
}