#ifndef SPARSESYSTEMS_INITIALNODEMETHODS_H
#define SPARSESYSTEMS_INITIALNODEMETHODS_H

/* МЕТОДЫ ДЛЯ ЛР № 4 (Поиск начального узла)*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include "RootLevelMethods.h"
#include <vector>

/** Поиск начального узла (ЛР4)
 *
 * @param NP        - количество узлов
 * @param XADJ      - массив для статической матрицы
 * @param ADJ      - массив для статической матрицы
 *
 * */
size_t Find_Initial_Node(size_t& NP, std::vector<size_t>& XADJ, std::vector<size_t>& ADJ);

#endif //SPARSESYSTEMS_INITIALNODEMETHODS_H
