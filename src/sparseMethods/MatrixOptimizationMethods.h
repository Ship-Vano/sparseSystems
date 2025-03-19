#ifndef SPARSESYSTEMS_MATRIXOPTIMIZATIONMETHODS_H
#define SPARSESYSTEMS_MATRIXOPTIMIZATIONMETHODS_H

/* МЕТОДЫ ДЛЯ ЛР № 5 ( Разработка программы оптимизации нумерации узлов сетки
обратным методом Катхилла-МакКи)*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include "InitialNodeMethods.h"
#include "RootLevelMethods.h"

#include <vector>


// компаратор для сортировки старых номеров узлов
bool cmp_RCM(const std::vector<size_t>& v1, const std::vector<size_t>& v2);



/** Алгоритм Катхилла---Макки (ЛР5)
 *
 * @param NP        - количество узлов
 * @param XADJ      - массив для статической матрицы
 * @param ADJ      - массив для статической матрицы
 * @param RCM       - Вектор перестановки
 * @param IRCM      - Вектор обратной перестановки
 * @param XENV      - Новый массив для статической матрицы жёсткости (1)
 * @param ENV      - Новый массив для статической матрицы жёсткости (2)
 *
 * */
void Reverse_Cuthill_Mckey(size_t& NP, std::vector<size_t>& XADJ, std::vector<size_t>& ADJ,\
                            std::vector<size_t>& RCM, std::vector<size_t>& IRCM,\
                            std::vector<size_t>& XENV, std::vector<size_t>& ENV);

// Функция проверки ребра i <-> j
bool Is_Neighbours(const size_t i, const size_t j, const std::vector<size_t>& xadj, const std::vector<size_t>& adj);

// Функция вычисления размера оболочки
size_t Span_Size(const std::vector<size_t>& xadj, const std::vector<size_t>& adj, size_t& NP);

#endif //SPARSESYSTEMS_MATRIXOPTIMIZATIONMETHODS_H
