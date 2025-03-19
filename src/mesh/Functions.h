/*
 *  ОБЪЯВЛЕНИЕ ФУНКЦИЙ ЛАБОРАТОРНОЙ РАБОТЫ
 *
 **/

#pragma once
#include <iostream>
#include <vector>    // Для доступа к vector
#include <fstream>   // Для работы с файлами
#include <cmath>     // Для хз
#include <array>
#include <string>

const double EPS = 1e-16; // Машинный ноль

//int NP = 0;   // Количество точек (2 - прямая, 4 - плоскость)
//int NE1 = 0;  // Количество элементов
//int NE2 = 0;  // на линии
//int type = 0; // Тип элемента

/* Перегрузка оператора "*" для double и vector */
std::vector<double> operator*(const double& a, const std::vector<double>& vec);

/* Перегрузка оператора "+=" для vector и vector */
std::vector<double> operator+=(std::vector<double>& vec1, const std::vector<double>& vec2);

/* Перегрузка оператора "cout" для vector */
std::ostream& operator<<(std::ostream& str, const std::vector<double>& vec);

/* Вычисление определителя квадратной матрицы 2 порядка */
double My_det2(const double& a11, const double& a12, const double& a21, const double& a22);

/* Вычисление первого неизвестного методом крамера */
double My_get_par(const double& a11, const double&  a12,
                  const double&  a21, const double&  a22, const double&  b1, const double& b2);

/* Функция чтения из файла */
std::vector<std::vector<double>> My_Read_File(const std::string file, int& NP, int& NE1, int& NE2, int& type);

/** Функция вычисляет координаты узла пересечения двух линий в трёхмерном пространстве
 * (или проверяет их наличие)
 *
 * @param v1 - точка 1
 * @param v2 - точка 2
 * @param v3 - точка 3
 * @param v4 - точка 4
 *
 * @return Если пересечение найдено, вычисляется параметрическое представление точки,
 * и возвращается её положение в виде трёхмерного вектора
 */
std::vector<double> My_nodes(const std::vector<double>& v1, const std::vector<double>& v2,
                             const std::vector<double>& v3, const std::vector<double>& v4);

/** Функция - Построение сетки для отрезка (1D)
 *
 * @param Points - Начальная и конечная точки отрезка
 * @param file - Имя файла для записи
 * @param NP - Кол-во узлов
 * @param NE1 - Кол-во элементов
 * @param type - тип сетки (1 - линейная, 2 - квадратичная)
 *
 * @return В файл записываются:
 * - информация об элементах (их узлы)
 * - координаты узлов, равномерно распределённых вдоль отрезка
 * - номера узлов на концах отрезка
 *  true - при успешной записи файл, false иначе
 */
bool My_Write_File_2(const std::vector<std::vector<double>>& Points, const std::string& file,
                     const int&  NP, const int& NE1, const int& type);

/** Функция - Построение сетки для участка плоскости (2D),
 *  определенной 4-мя вершинами (подразумевается прямоугольник)
 *
 * @param Points - Координаты узлов прямоугольника
 * @param file - Имя файла для записи
 * @param NP - Кол-во узлов
 * @param NE1 - Кол-во узлов по оси Ox
 * @param NE2 - Кол-во узлов по оси Oy
 * @param type - Тип разбиения (обычное, диагональное, центральное)
 * @return В файл записывается:
 * - информация об элементах (их узлы)
 * - координаты узлов
 * - номера узлов на границе области
 *  true - при успешной записи файл, false иначе
 */
bool My_Write_File_4(const std::vector<std::vector<double>>& Points, const std::string& file,
                     const int& NP, const int& NE1, const int& NE2, const int& type);

