/*
 *  ОБЪЯВЛЕНИЕ ФУНКЦИЙ ЛАБОРАТОРНОЙ РАБОТЫ
 *
 **/

#include "Functions.h"


/* Перегрузка оператора "*" для double и vector */
std::vector<double> operator*(const double& a, const std::vector<double>& vec) {
    std::vector<double> res = vec;

    for (auto& w : res) {
        w *= a;
    }
    return res;
};


/* Перегрузка оператора "+=" для vector и vector */
std::vector<double> operator+=(std::vector<double>& vec1, const std::vector<double>& vec2) {
    size_t n = vec1.size();

    for (size_t i = 0; i < n; ++i) {
        vec1[i] += vec2[i];
    }
    return vec1;
};


/* Перегрузка оператора "cout" для vector */
std::ostream& operator<<(std::ostream& str, const std::vector<double>& vec) {
    for (auto& w : vec) {
        str << w << " ";
    }

    return str;
}


/* Вычисление определителя квадратной матрицы 2 порядка */
double My_det2(const double& a11, const double& a12, const double& a21, const double& a22) {
    return a11 * a22 - a12 * a21;
}


/* Вычисление первого неизвестного методом крамера */
double My_get_par(const double& a11, const double&  a12, const double&  a21,
                  const double&  a22, const double&  b1, const double&  b2) {
    return My_det2(b1, a12, b2, a22) / My_det2(a11, a12, a21, a22);
}


/* Функция для получения параметров задачи из текстового файло */
std::vector<std::vector<double>> My_Read_File(const std::string file,
                                              int& NP, int& NE1, int& NE2, int& type) {

    std::ifstream Fin(file);

    if (!Fin.is_open()) {
        std::cout << "[LOG]: " << "File " << file << " is NOT open." << std::endl;
        std::vector<std::vector<double>> b(0, std::vector<double>(0));
        return b;
    } else {

        Fin >> NP;

        std::vector<std::vector<double>> Points(NP); // Массив данных точек
        for (size_t i = 0; i < NP; ++i) {
            Points[i].resize(3); // Каждая точка из R3
        }
        for (size_t i = 0; i < NP; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                Fin >> Points[i][j];
            }
        }

        Fin >> NE1;

        if (NP == 4)
            Fin >> NE2;

        Fin >> type;

        Fin.close();
        std::cout << "[LOG]: " << "Parametres on file " << file << " are received." << std::endl;
        std::cout << "[LOG]: " << "Your parametres is: " << std::endl;
        std::cout << "[LOG]: " << "NP = "   << NP   << /*" --- кол-во точек," <<*/                std::endl;
        std::cout << "[LOG]: " << "NE1 = "  << NE1  <</* " --- кол-во элементов на линии 1," <<*/ std::endl;
        std::cout << "[LOG]: " << "NE2 = "  << NE2  << /*" --- кол-во элементов на линии 2," << */std::endl;
        std::cout << "[LOG]: " << "Type = " << type <</* "--- тип элемента." << */                std::endl;
        return Points;
    }
}
