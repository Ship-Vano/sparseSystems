#include "AdjacencyMethods.h"

void
Dynamic_Add(const size_t i, const size_t j, std::vector<int> &HEAD, std::vector<size_t> &NBRS, std::vector<int> &LINK) {
    LINK.push_back((int)HEAD[i - 1]);
    NBRS.push_back(j);
    HEAD[i - 1] = int(NBRS.size());
}

bool
Dynamic_Check(const size_t i, const size_t j, std::vector<int> &HEAD, std::vector<size_t> &NBRS, std::vector<int> &LINK) {
    size_t k = 0;

    if (HEAD[i - 1] < 0)
        return 0;

    k = HEAD[i - 1] - 1;

    while (NBRS[k] != j && LINK[k] > 0)
        k = LINK[k] - 1;

    return (NBRS[k] == j);
}

void Dynamic_Matrix(std::vector<int> &HEAD, std::vector<size_t> &NBRS, std::vector<int> &LINK, size_t &NP, size_t &NE,
                    size_t &elem_t, std::vector<size_t> &Elem) {
    HEAD.resize(NP, -1);

    size_t curr_i = 0;
    size_t curr_j = 0;

    for (size_t i = 0; i < NE; ++i)
    {
        for (size_t j = 0; j < elem_t; ++j)
            for (size_t k = j + 1; k < elem_t; ++k)
            {
                curr_i = Elem[elem_t * i + j];
                curr_j = Elem[elem_t * i + k];

                if (!Dynamic_Check(curr_i, curr_j, HEAD, NBRS, LINK))
                {
                    Dynamic_Add(curr_i, curr_j, HEAD, NBRS, LINK);
                    Dynamic_Add(curr_j, curr_i, HEAD, NBRS, LINK);
                }
            }
    }
}

void
Static_Matrix(std::vector<int> &HEAD, std::vector<size_t> &XADJ, std::vector<size_t> &ADJ, std::vector<size_t> &NBRS,
              std::vector<int> &LINK, size_t &NP) {
    int k = 0;

    size_t it = 0;

    for (size_t i = 0; i < NP; ++i)
    {
        k = HEAD[i] - 1;
        XADJ.push_back(ADJ.size() + 1);

        it = ADJ.size();

        while (k > -1)
        {
            ADJ.push_back(NBRS[k]);
            k = LINK[k] - 1;
        }

        std::sort(ADJ.begin() + it, ADJ.end());
    }

    XADJ.push_back(ADJ.size() + 1);
    ADJ.push_back(0);
}
