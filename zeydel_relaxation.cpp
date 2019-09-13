#include "zeydel_relaxation.h"
#include "convinient_system.h"
#include "jacoby.h"
#include "iter_solution.h"
#include "norm_error.h"

#include "eps.h"



double norm_zeidel(vector<vector<double>> &matrix, double w){
    

    vector<vector<double>> diag_down_matrix(matrix.size(), vector<double> (matrix.size()));
    for (int i = 0; i < matrix.size(); i ++){
        for (int j = 0; j < matrix.size(); j ++){
            diag_down_matrix[i][j] = matrix[i][j];

            if (i != j){
                diag_down_matrix[i][j] = w * diag_down_matrix[i][j]; //ДОМНОЖАЕМ НА ПАРАМЕТР W МАТРИЦУ D
            }

            if (j > i){
                diag_down_matrix[i][j] = 0;
            }
        }
    }

    // cout << "НИЖНЕТРЕУГОЛЬНАЯ" << endl;
    //     for (const auto &v:diag_down_matrix){
    //         for (const auto &n: v){
    //             cout << n << "   ";
    //         }
    //         cout <<  endl;
    //     }

    // cout <<  endl;



    vector<vector<double>> diag_up_matrix(matrix.size(), vector<double> (matrix.size()));

    for (int i = 0; i < matrix.size(); i ++){
        for (int j = 0; j < matrix.size(); j ++){
            diag_up_matrix[j][i] = diag_down_matrix[i][j];//ТРАНСПОНИРУЕМ
        }
    }

    // cout << "ВЕРХНЕТРЕУГОЛЬНАЯ" << endl;
    // for (const auto &v:diag_up_matrix){
    //     for (const auto &n: v){
    //         cout << n << "   ";
    //     }
    //     cout <<  endl;
    // }

    // cout <<  endl;




    vector<vector<double>> reverse_up_matrix(matrix.size(), vector<double> (matrix.size()));

    for (int i = 0; i < matrix.size(); i ++){
        reverse_up_matrix[i][i] = 1/diag_up_matrix[i][i];// ОБРАТИЛИ ЭЛЕМЕНТЫ НА ГЛАВНОЙ ДИАГОНАЛИ
    }

    //НАЙДЕМ ОБРАТНУЮ К ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЕ
    for (int i = 0; i < matrix.size(); i ++){
        for (int j = 0; j < matrix.size(); j ++){
            double sum = 0;
            for (int k = 0; k <= j; k ++){
                sum += reverse_up_matrix[i][k] * diag_up_matrix[k][j];
            }

            reverse_up_matrix[i][j] = (-1/diag_up_matrix[j][j] * sum);

        }
    }


    // cout << "ПОЛУЧЕННАЯ МАТРИЦА. ОБРАТНАЯ" << endl;
    // for (const auto &v:reverse_up_matrix){
    //     for (const auto &n: v){
    //         cout << -n << "   ";
    //     }
    // cout <<  endl;
    // }

    // cout <<  endl;

    //ТРАНСПОНИРУЕМ ПОЛУЧЕННУЮ МАТРИЦУ
    vector<vector<double>> reverse_down_matrix(matrix.size(), vector<double> (matrix.size()));

    for (int i = 0; i < matrix.size(); i ++){
        for (int j = 0; j < matrix.size(); j ++){
            reverse_down_matrix[i][j] = -reverse_up_matrix[j][i];//СРАЗУ ТРАНСПОНИРУЕМ

        }
    }

    // cout << "ПОЛУЧЕННАЯ МАТРИЦА. НИЖНЕТРЕУГОЛЬНАЯ" << endl;
    //     for (const auto &v:reverse_down_matrix){
    //         for (const auto &n: v){
    //             cout << n << "   ";
    //         }
    //     cout <<  endl;
    //     }
    // cout <<  endl;


    //НАЙДЕМ МАТРИЦУ (D + wL - A)
    vector<vector<double>> d_l_a_matrix(matrix.size(), vector<double> (matrix.size()));

    for (int i = 0; i < d_l_a_matrix.size(); i++){
        for (int j = 0 ; j < d_l_a_matrix.size(); j ++){
            d_l_a_matrix[i][j] = diag_down_matrix[i][j] - matrix[i][j];
        }

    }

    // cout << "МАТРИЦА D + L + A" << endl;
    //     for (const auto &v:d_l_a_matrix){
    //         for (const auto &n: v){
    //             cout << n << "   ";
    //         }
    //         cout <<  endl;
    //     }
    // cout <<  endl;



    //ПЕРЕМНОЖИМ ПОЛУЧЕННЫЕ МАТРИЦЫ
    vector<vector<double>> product_matrix(matrix.size(), vector<double> (matrix.size()));

    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            for (int k = 0; k < matrix.size(); k++){
                product_matrix[i][j] += reverse_down_matrix[i][k] * d_l_a_matrix[k][j];
            }
            
        }
    }

    // cout << "МАТРИЦА С" << endl;
    // for (const auto &v:product_matrix){
    //     for (const auto &n: v){
    //         cout << n << "   ";
    //     }
    // cout <<  endl;
    // }
    // cout <<  endl;


    //НАЙДЕМ НОРМУ МАТРИЦЫ С
    double norm = 0;
    double max_row_c = 0;
    double sum_row_c= 0;
    for (int i = 0; i < product_matrix.size(); i++){
        sum_row_c = 0;
        for (int j = 0; j < product_matrix.size(); j++){
            sum_row_c += fabs(product_matrix[i][j]);

        }
        if (sum_row_c > max_row_c){
            max_row_c = sum_row_c;
        }
    }

    cout << "НОРМА МАТРИЦЫ С(МЕТОДА ЗЕЙДЕЛЯ, РЕЛАКСАЦИИ) =  " << max_row_c << endl;

    return max_row_c;
}

//ФУНКЦИЯ ПРИВЕДЕНИЯ МАТРИЦЫ К УДОБНОМУ ВИДУ (МЕТОД ЗЕЙДЕЛЯ, РЕЛАКСАЦИИ)
std::vector<std::vector<double>> zeydel_relaxation_matrix(std::vector<std::vector<double>> &matrix, vector<double> &changed_vector_zeydel, double &norm_zeydelC){
	
	std::vector<std::vector<double>> result_convinient_matrix_zeydel = convinient_matrix_jacoby(matrix, changed_vector_zeydel, norm_zeydelC);


	return result_convinient_matrix_zeydel;

}

//НОРМА КУБИЧЕСКАЯ ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ
double norm_up_triangle(std::vector<std::vector<double>> &matrix){
    double max_row = 0;
     
    for (int i = 0; i < matrix.size(); i++){
        double temp_max_row = 0;
        for (int j = 1 + i; j < matrix.size(); j ++){
            temp_max_row += fabs(matrix[i][j]);
        }

        if (temp_max_row > max_row){
            max_row = temp_max_row;
        }
    }
    return max_row;

}

//ФУНКЦИЯ НАХОЖДЕНИЯ РЕШЕНИЯ(МЕТОД ЗЕЙДЕЛЯ, РЕЛАКСАЦИИ)
vector<double> zeydel_relax_solution(double &parametr, std::vector<std::vector<double>> &matrix_zeydel, vector<double> &changed_vector_zeydel, double norm_B, double &parametr_apost){

    // cout << "Норма матрицы, приведенной к удобному виду" << norm_B << endl;

    //     cout << "МАТРИЦА B" << endl;
    // for (const auto &v:matrix_zeydel){
    //     for (const auto &n: v){
    //         cout << n << "   ";
    //     }
    // cout <<  endl;
    // }
    // cout <<  endl;

	//НОРМА ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ
	double norm_B2 = norm_up_triangle(matrix_zeydel);

	//НОВОЕ ЗНАЧЕНИЕ ЭПСИОЛОН
    
	double EPS2 = (1 - norm_B)/(norm_B2)* EPSILON;

    parametr_apost = (1 - norm_B)/(norm_B2);

	//ВЫЛЕЛЯЕМ ПАМЯТЬ ПОД ВЕКТОРА РЕШЕНИЙ(ТЕКУЩИЙ И ПРЕДЫДУЩИЙ)
	vector<double> init_solution(matrix_zeydel.size());
    vector<double> new_solution(matrix_zeydel.size());


    //ПУСТЬ НАЧАЛЬНЫМ ПРИБЛЕЖНИЕМ БУДЕТ НУЛЕВОЙ ВЕКТОР
    for (int i = 0; i < matrix_zeydel.size(); i ++){
        init_solution[i] = 0;
        new_solution[i] = 0;
    }
    
    //РАЗНОСТЬ X^N И X^(N-1) РЕШЕНИЙ
    std::vector<double> vector_difference(matrix_zeydel.size());

    //НОРМА РАЗНОСТИ X^N И X^(N-1) РЕШЕНИЙ
    double norm_difference = 1;

    int amount_iter = 0;
    while(norm_difference >= EPS2){

        //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
        for (int i = 0; i < matrix_zeydel.size(); i ++){
            init_solution[i] = new_solution[i];
            new_solution[i] = 0;
        }

        for (int i = 0; i < matrix_zeydel.size(); i ++){
        	for (int j = 0; j < matrix_zeydel.size(); j ++){
        		//ПОДСЧЕТ УМНОЖЕНИЯ НИЖНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ИЗМЕНЕННЫЙ ВЕКТОР
        		double product_B1_xnew = 0;
        		for (int k = 0; k < i; k ++){
        			product_B1_xnew += matrix_zeydel[i][k] * new_solution[k];
        		}
        		

        		//ПОДСЧЕТ УМНОЖЕНИЯ ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ПЕРВОНАЧАЛЬНЫЙ ВЕКТОР
        		double product_B2_xold = 0;
        		for (int k = 1 + i; k < matrix_zeydel.size(); k++){
        			product_B2_xold += matrix_zeydel[i][k] * init_solution[k];
        		}

        		new_solution[i] = (1 - parametr) * init_solution[i] + parametr * product_B1_xnew + parametr * product_B2_xold + parametr * changed_vector_zeydel[i];
        	}

            double l = norm_error(new_solution);
            if (l <= EPSILON){
                cout << "достииигнууууууууууутаааааааааа   " << amount_iter << endl;
            }

        }


        for (int i = 0; i < matrix_zeydel.size(); i++){
            vector_difference[i] = new_solution[i] - init_solution[i];
        }

        //НОРМА ВЕКТОРА РАЗНОСТИ
        norm_difference = norm_vector(vector_difference);
        amount_iter++;

    }

    cout << "Количество итераций  = " << amount_iter << endl;
    //Для априорной оценки
    // int k =0;
    // double norm_y = norm_vector_right_part(changed_vector_zeydel);
    // while (k <= (log(EPS2 * (1 - norm_B)/(norm_y))/log(norm_B))){ //ОБНУЛЯЕМ НОВЫЙ ВЕКТОР РЕШЕНИЙ
    //     for (int i = 0; i < matrix_zeydel.size(); i ++){
    //         init_solution[i] = new_solution[i];
    //         new_solution[i] = 0;
    //     }

    //     for (int i = 0; i < matrix_zeydel.size(); i ++){
    //         for (int j = 0; j < matrix_zeydel.size(); j ++){
    //             //ПОДСЧЕТ УМНОЖЕНИЯ НИЖНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ИЗМЕНЕННЫЙ ВЕКТОР
    //             double product_B1_xnew = 0;
    //             for (int k = 0; k < i; k ++){
    //                 product_B1_xnew += matrix_zeydel[i][k] * new_solution[k];
    //             }
                

    //             //ПОДСЧЕТ УМНОЖЕНИЯ ВЕРХНЕТРЕУГОЛЬНОЙ МАТРИЦЫ НА ПЕРВОНАЧАЛЬНЫЙ ВЕКТОР
    //             double product_B2_xold = 0;
    //             for (int k = 1 + i; k < matrix_zeydel.size(); k++){
    //                 product_B2_xold += matrix_zeydel[i][k] * init_solution[k];
    //             }
    //             // cout << "changed_vector_zeydel" << changed_vector_zeydel[i] << endl;
    //             new_solution[i] = (1 - parametr) * init_solution[i] + parametr * product_B1_xnew + parametr * product_B2_xold + parametr * changed_vector_zeydel[i];
    //         }

    //     }


    //     for (int i = 0; i < matrix_zeydel.size(); i++){
    //         vector_difference[i] = new_solution[i] - init_solution[i];
    //     }
    //     //НОРМА ВЕКТОРА РАЗНОСТИ
    //     norm_difference = norm_vector(vector_difference);

    //     k++;
    // }
    // cout << "Количество итераций, априорная оценка = " << k << endl;

    // double aprior_error = (pow(norm_B, k))/(1 - norm_B)*norm_y;
    // cout << "Априорная оценка погрешности = " << aprior_error << endl;

    return new_solution;



}

