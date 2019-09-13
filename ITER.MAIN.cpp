#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <math.h>

#include "function_read_matrix.h"
#include "convinient_system.h"
#include "iter_solution.h"
#include "jacoby.h"
#include "zeydel_relaxation.h"
#include "big_matrix.h"
#include "nevyazka.h"
#include "norm_error.h"
#include "eps.h"


using namespace std;





int main(){

    vector<std::string> test_names = {"/home/darya/Method_of_calculation/LabaSecond/_Lab2/ITER/BASE1.TXT"};
                                      //"/home/darya/Method_of_calculation/LabaSecond/_Lab2/ITER/BASE2.TXT",
                                      //"/home/darya/Method_of_calculation/LabaSecond/_Lab2/ITER/ITER1_WITHOUT_SOL.TXT"};
                                      // "/home/darya/Method_of_calculation/LabaSecond/_Lab2/ITER/ITER4.TXT",
                                      // "/home/darya/Method_of_calculation/LabaSecond/_Lab2/ITER/ITER5.TXT"};


    int i = 0;
    double temp_iter_parametr = 1;
    std::vector<double> vectorY;
    double norm_C = 1;
    bool diverges = false;
    //ДЛЯ ПЕРВОГО ТЕСТА
    vector<double> precise_sol = {5, -7, 12, 4};

    //ДЛЯ ВТОРОГО ТЕСТА
    //vector<double> precise_sol = {10, -10, 12, 4};

    // ДЛЯ 13 ТЕСТА
    //vector<double> precise_sol = {-7, 7, 2, -6};

    // ДЛЯ 3 ТЕСТА
    //vector<double> precise_sol = {2, -5, 12, 3};
    //double  norm_precise_sol = norm_vector_right_part(precise_sol);
    double  norm_precise_sol = 12;



    for (const auto &s: test_names){
        cout << "                                       ТЕСТ " << i + 1 << endl;
        cout<< "Считанная расширенная матрица из файла" << endl;
        double norm_C = 1;
        
        std::vector<std::vector<double>> matrix = open_test_read_slae(s);
        double eps_new;

        //МЕТОД ПРОСТОЙ ИТЕРАЦИИ
        cout << "МЕТОД ПРОСТОЙ ИТЕРАЦИИ" << endl;
        bool diverges = false;
        std::vector<std::vector<double>> convinient_one = convinient_matrix(matrix, temp_iter_parametr, vectorY, norm_C);

        //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        //double eps_new = norm_C/(1 - norm_C) * EPSILON;
        int n = log(EPSILON/norm_precise_sol)/log(norm_C);
        cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ = " << n << endl;
        //КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ
        
        cout << "Итерационный параметр: " << temp_iter_parametr << endl;
        vector<double> solution = iter_solution(convinient_one, vectorY, norm_C, diverges);
        if(diverges == true){
            cout << "Метод расходится" << endl;
        }
        else {
            cout << "Решение при использовании метода простой итераии" << endl;
            for (const auto &n: solution){
                cout <<setprecision(9) << fixed <<  n << endl;
            }

            // nevyazka(matrix,solution); 
            // double error_norm_iter = norm_error(solution);
            // cout << "Апостериорная оценка метод простой итерации" << endl;
            // double apost_iter = (norm_C/(1 - norm_C))* error_norm_iter;
            // cout << apost_iter << endl;

        }


        //НОРМА ВЕКТОРА РЕШЕНИЯ ПРАВОЙ ЧАСТИ ИЗМЕНЕННОЙ МАТРИЦЫ
        double norm_y = norm_vector_right_part(vectorY);
        
        
        //КОНЕЦ МЕТОДА ПРОСТОЙ ИТЕРАЦИИ 
    diverges = false;

    МЕТОД ЯКОБИ
        double normC_jacoby = 1;
        std::vector<double> changed_vector_jacoby;
        cout << "\nМЕТОД ЯКОБИ" << endl;
        std::vector<std::vector<double>> matrix_jacoby = convinient_matrix_jacoby(matrix, changed_vector_jacoby, normC_jacoby);

        //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        eps_new = normC_jacoby/(1 - normC_jacoby)* EPSILON;
        n = log(EPSILON/norm_precise_sol)/log(normC_jacoby);
        cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ = " << n << endl;
        //КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ


        cout <<"\nНорма матрицы = " << normC_jacoby << endl;
        if (normC_jacoby > 1){
            cout << "Метод расходится. Норма матрицы > 1";
        }

        else{
            vector<double> solution_jacoby = jacoby_solution(matrix_jacoby, changed_vector_jacoby, normC_jacoby, diverges);
            nevyazka(matrix,solution_jacoby); 
            double error_norm_jacoby =  norm_error(solution_jacoby);

            cout << "Апостериорная оценка метод Якоби" << endl;
            double apost_jacoby = normC_jacoby/(1 - normC_jacoby) * error_norm_jacoby;
            cout << apost_jacoby << endl;

            cout << "Решение при использовании метода Якоби" << endl;
            for (const auto &n:solution_jacoby){
                cout << n <<endl;
            }

        }
    //КОНЕЦ МЕТОДА ЯКОБИ
    diverges = false;

    //МЕТОД ЗЕЙДЕЛЯ
        cout << "\nМЕТОД ЗЕЙДЕЛЯ" << endl;
        double parametr = 1;
        double norm_zeuydel_relax = 1;
        double parametr_apost = 1;
        std::vector<double> vector_zeydel_relax;

        std::vector<std::vector<double>> matrix_seydel_relax = zeydel_relaxation_matrix(matrix, vector_zeydel_relax, normC_jacoby);

        //НОРМА МАТРИЦЫ С(ЗЕЙДЕЛЬ, РЕЛАКСАЦИЯ)
        norm_zeuydel_relax = norm_zeidel(matrix, parametr);

        if (norm_zeuydel_relax > 1){
            cout << "Метод расходится. Норма матрицы > 1";
        }
        else{
            vector<double> solution_zeyd_relax = zeydel_relax_solution(parametr, matrix_seydel_relax, vector_zeydel_relax, normC_jacoby, parametr_apost);
            nevyazka(matrix,solution_zeyd_relax); 
            double error_norm_zeidel = norm_error(solution_zeyd_relax);

            cout << "Апостериорная оценка метод Зейделя" << endl;
            double apost_zeidel = 1/parametr_apost * error_norm_zeidel;
            cout << apost_zeidel << endl;

            cout << "Решение методом Зейделя" << endl;
            for(const auto &n: solution_zeyd_relax){
                cout << n << endl;
            }

        }


        //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        n = log(EPSILON/norm_precise_sol)/log(norm_zeuydel_relax);
        cout << norm_zeuydel_relax << endl;
        cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ = " << n << endl;
        //КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ

        //КОНЕЦ МЕТОДА ЗЕЙДЕЛЯ


        //МЕТОД РЕЛАКСАЦИИ
        cout << "\nМЕТОД РЕЛАКСАЦИИ" << endl;
        double parametr_relax = 1.4;
        double norm_relax = 1;
        parametr_apost = 1;
        std::vector<double> vector_relax;

        std::vector<std::vector<double>> matrix_relax = zeydel_relaxation_matrix(matrix, vector_relax, norm_relax);
        norm_relax = norm_zeidel(matrix, parametr_relax);

        if (norm_relax > 1){
            cout << "Метод расходится. Норма матрицы > 1";
        }
        else{
            vector<double> solution_relax = zeydel_relax_solution(parametr_relax, matrix_relax, vector_relax, normC_jacoby, parametr_apost);
            nevyazka(matrix,solution_relax); 
            double error_norm_relax = norm_error(solution_relax);

            cout << "Апостериорная оценка метод Релаксации" << endl;
            double apost_relax = norm_relax/(1 - norm_relax) * error_norm_relax;
            cout << apost_relax << endl;

            cout << "Решение методом Релаксации" << endl;
            for(const auto &n: solution_relax){
                cout << n << endl;
            }
        }



        //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        //n = log(EPSILON/norm_precise_sol) /log(norm_relax);
        double a = norm_vector_right_part(vector_relax);
        n = log((EPSILON*(1-norm_relax)/a)) /log(norm_relax);
        cout << norm_relax << endl;
        cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ = " << n << endl;
        КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ

        КОНЕЦ МЕТОДА РЕЛАКСАЦИИ

       i++;
    }

    //БОЛЬШАЯ ТРЕХДИАГОНАЛЬНАЯ МАТРИЦА
        // const int N = 213;

        // // //ПАРАМЕТР ДЛЯ МЕТОДА ЗЕЙДЕЛЯ
        // double parametr_big_matrix_zeidel = 1;

        // //СОЗДАНИЕ МАТРИЦЫ
        // auto threediag = creation_big_matrix(N);

        // //ПРИВДЕНИЕ К УДОБНОМУ ВИДУ
        // auto threediag_convinient = convinient_big_matrix(threediag);

        // //НАХОЖДЕНИЕ НОРМЫ
        // auto matr_big = make_big_matrix(N);
        // double norm_big_matr = norm_zeidel(matr_big, parametr_big_matrix_zeidel);

        // double norm_big = norm_b(threediag_convinient);
        // norm_precise_sol = 2;



        // vector<double> solution_big_matr_zeidel = solution_big_matrix(threediag_convinient, norm_big, parametr_big_matrix_zeidel);
        // cout << "Решение методом Зейделя СЛАУ с трехдиагональной матрицы" << endl;

        // cout << "Норма порешности" << endl;
        // double norm_big_matrix = norm_error_big_matrix(solution_big_matr_zeidel);
        // cout << norm_big_matrix << endl;

        // cout << "Норма невязки" << endl;
        // double nevyazka_big = nevyazka_big_matrix(threediag, solution_big_matr_zeidel, N);
        // cout << nevyazka_big << endl;

        // //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        // double eps_new;
        // // if (norm_big <=1/2){
        // // eps_new = EPSILON;
        // // }
        // // else{
        // //     eps_new = (1 - norm_big)/ norm_big * EPSILON;
        // // }
        // //eps_new = (1 - norm_big)/ 0.25 * EPSILON;
        // int n = log(EPSILON/norm_precise_sol)/log(norm_big_matr);
        // cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ. метод релаксации = " << n << endl;
        // //КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ


        // cout << "Апостериорная оценка погрешности, метод Зейделя, большая матрица" << endl;
        // double apost_big_matrix_zeidel = norm_big/(1 - norm_big) * norm_big_matrix;
        // cout << apost_big_matrix_zeidel << endl;


        // cout << "Решение методом релаксации СЛАУ с трехдиагональной матрицы" << endl;
        // double parametr_big_matrix_relax = 1.5;
        // norm_big_matr = norm_zeidel(matr_big, parametr_big_matrix_relax);
        // vector<double> solution_big_matr_relax = solution_big_matrix(threediag_convinient, norm_big, parametr_big_matrix_relax);

        // cout << "Норма порешности" << endl;
        // double norm_big_relax = norm_error_big_matrix(solution_big_matr_relax);
        // cout << norm_big_relax << endl;

        // cout << "Норма невязки" << endl;

        // double nevyazka_big_relax = nevyazka_big_matrix(threediag, solution_big_matr_relax, N);
        // cout << nevyazka_big_relax << endl;

        // //АПРИОРНАЯ ОЦЕНКА КОЛИЧЕСТВА ИТЕРАЦИЙ
        // // if (norm_big <=1/2){
        // // eps_new = EPSILON;
        // // }
        // // else{
        // //     eps_new = (1 - norm_big)/ norm_big * EPSILON;
        // // }

        // //eps_new = (1 - norm_big)/ 0.25 * EPSILON;
        // //cout << norm_big_matr << endl;
        // n = log(EPSILON/norm_precise_sol)/log(norm_big_matr);
        // cout << "АПРИОРНАЯ оценка КОЛИЧЕСТВА ИТЕРАЦИЙ. метод релаксации = " << n << endl;
        // //КОНЦЕ ВЫЧИСЛЕНИЯ АПРИОРНОЙ ОЦЕНКИ КОЛИЧЕСТВА ИТЕРАЦИЙ

        // cout << "Апостериорная оценка погрешности, метод релаксации, большая матрица" << endl;
        // double apost_big_matrix_relax = norm_big/(1 - norm_big) * norm_big_relax;
        // cout << apost_big_matrix_relax << endl;
    

    return 0;
}
