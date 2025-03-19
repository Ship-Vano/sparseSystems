
#ifndef SPARSESYSTEMS_ROOTLEVELMETHODS_H
#define SPARSESYSTEMS_ROOTLEVELMETHODS_H

/* МЕТОДЫ ДЛЯ ЛР № 3 (Построение корневой структуры уровней)*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include <vector>
#include <algorithm>

/** Сравнение количества соседей (ЛР3)
 *
 * @param i         - индекс i
 * @param j         - индекс j
 * @param XADJ      - массив для статической матрицы
 *
 * */
struct Comparator {
    Comparator(std::vector<size_t>& XADJ) { this->XADJ = XADJ; }
    bool operator () (const size_t i, const size_t j) {
        return XADJ[i] - XADJ[i - 1] < XADJ[j] - XADJ[j - 1];
    }

    std::vector<size_t> XADJ;
};


/** Построение корневой структуры уровней(ЛР3)
 *
 * @param root      - корневой элемент
 * @param XADJ      - массив для статической матрицы
 * @param ADJ      - массив для статической матрицы
 * @param NP        - количество узлов
 *
 * */
std::vector<std::vector<size_t>> Level_Structure(size_t& root, std::vector<size_t>& XADJ, std::vector<size_t>& ADJ, size_t& NP);


#endif //SPARSESYSTEMS_ROOTLEVELMETHODS_H
