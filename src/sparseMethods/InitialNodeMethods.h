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
size_t Find_Initial_Node(size_t& NP, std::vector<size_t>& XADJ, std::vector<size_t>& ADJ)
{
    size_t res = 1;
    size_t buf = 1;
    size_t prev_size = 0;
    size_t prev_nbrs = 0;
    size_t degree = 0;
    size_t min_degree = NP;

    std::vector<std::vector<size_t>> lev_struct;

    do
    {
        res = buf;

        lev_struct = Level_Structure(res, XADJ, ADJ, NP);

        min_degree = NP;
        prev_size = lev_struct.size();
        prev_nbrs = lev_struct.back().size();

        for (const auto& w : lev_struct.back())
        {
            degree = XADJ[w] - XADJ[w - 1];

            if (degree < min_degree)
            {
                min_degree = degree;
                buf = w;
            }
        }

        lev_struct = Level_Structure(buf,XADJ, ADJ, NP);
    } while (lev_struct.size() > prev_size || lev_struct.back().size() > prev_nbrs);

    return res;
}

#endif //SPARSESYSTEMS_INITIALNODEMETHODS_H
