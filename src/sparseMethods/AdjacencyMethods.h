#ifndef SPARSESYSTEMS_ADJACENCYMETHODS_H
#define SPARSESYSTEMS_ADJACENCYMETHODS_H

/* МЕТОДЫ ДЛЯ ЛР № 2 (Построение структуры смежности)*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include <vector>
#include <algorithm>

/** Добавление ребра i -> j
 *
 * @param i         - индекс i
 * @param j         - индекс j
 * @param HEAD      - массив для динамической матрицы
 * @param NBRS      - массив для динамической матрицы
 * @param LINK      - массив для динамической матрицы
 *
 * */
void Dynamic_Add(const size_t i, const size_t j, std::vector<int>& HEAD, std::vector<size_t>& NBRS, std::vector<int>& LINK);

/** Проверка наличия ребра i -> j
 *
 * @param i         - индекс i
 * @param j         - индекс j
 * @param HEAD      - массив для динамической матрицы
 * @param NBRS      - массив для динамической матрицы
 * @param LINK      - массив для динамической матрицы
 *
 * */
bool Dynamic_Check(const size_t i, const size_t j, std::vector<int>& HEAD, std::vector<size_t>& NBRS, std::vector<int>& LINK);

/**Процедура построения динамической матрицы смежности (ЛР2)
 *
 * @param HEAD      - массив для динамической матрицы
 * @param NBRS      - массив для динамической матрицы
 * @param LINK      - массив для динамической матрицы
 * @param NP        - количество узлов
 * @param NE        - количество элементов
 * @param elem_t    - тип элемента
 * @param Elem      - массив элементов
 *
 * */
void Dynamic_Matrix(std::vector<int>& HEAD, std::vector<size_t>& NBRS, std::vector<int>& LINK, \
                    size_t& NP, size_t& NE, size_t& elem_t, std::vector<size_t>& Elem);


/**Процедура построения статической матрицы смежности (ЛР2)
 *
 * @param HEAD      - массив для статической матрицы
 * @param XADJ      - массив для статической матрицы
 * @param ADJ       - массив для статической матрицы
 * @param NBRS
 * @param LINK
 * @param NP        - количество узлов
 *
 * */
void Static_Matrix(std::vector<int>& HEAD, std::vector<size_t>& XADJ, std::vector<size_t> &ADJ, \
                    std::vector<size_t>& NBRS, std::vector<int>& LINK, size_t& NP);

#endif //SPARSESYSTEMS_ADJACENCYMETHODS_H
