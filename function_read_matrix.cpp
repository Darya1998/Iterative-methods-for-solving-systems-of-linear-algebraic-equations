#include "function_read_matrix.h"


using namespace std;


std::vector<std::vector<double>> open_test_read_slae(std::string str);


std::vector<std::vector<double>> open_test_read_slae(std::string str){   
    ifstream file(str);
    if (!file.is_open()){
        cout << "Файл не может быть открыт! Имя файла:"<< str << endl;
        exit(EXIT_FAILURE);
    }

    //Считываем первую строку, т.к. нужные значения начинаются со второй
    std::string line;
    getline(file, line);
    //Закончили считывание первой строки
    std::vector<std::vector<double>> matrixV;
    while (std::getline(file, line)){
        if (line[0] == '\n' or line[0] == '\r'){
            break;
        }
        // cout<< line<< endl;
        std::istringstream iss(line);
        std::vector<double> data;
        double num;
        while(iss >> num){
            data.push_back(num);
        }
        matrixV.push_back(data);
    }

    for (const auto &v : matrixV){
        for (const auto &n: v){
            std::cout << left << setw(15)<< n << "\t";
        }
        std::cout << std::endl;
    }
    cout << endl << endl;
   
    return matrixV;
}