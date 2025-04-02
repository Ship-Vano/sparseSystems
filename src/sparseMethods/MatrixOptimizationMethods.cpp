#include "MatrixOptimizationMethods.h"

bool cmp_RCM(const std::vector<size_t> &v1, const std::vector<size_t> &v2) {
    return v1[1] < v2[1];
}

void Reverse_Cuthill_Mckey(size_t &NP, std::vector<size_t> &XADJ, std::vector<size_t> &ADJ, std::vector<size_t> &RCM,
                           std::vector<size_t> &IRCM, std::vector<size_t> &XENV, std::vector<size_t> &ENV) {
    size_t root = Find_Initial_Node(NP, XADJ, ADJ);

    std::vector<std::vector<size_t>> lev_struct = Level_Structure(root, XADJ, ADJ, NP);

    for (const auto& u : lev_struct)
        for (const auto& w : u)
            RCM.push_back(w);

    std::vector<std::vector<size_t>> permutation;

    std::vector<size_t> buf(2, 0);

    for (size_t i = 1; i <= NP; ++i)
    {
        buf = { i, RCM[i - 1] };
        permutation.push_back(buf);
    }

    std::sort(permutation.begin(), permutation.end(), cmp_RCM);

    for (const auto& w : permutation)
        IRCM.push_back(w[0]);

    size_t it = 0;

    for (const auto& w : RCM)
    {
        XENV.push_back(ENV.size() + 1);

        it = ENV.size();

        for (size_t i = XADJ[w - 1]; i < XADJ[w]; ++i)
            ENV.push_back(IRCM[ADJ[i - 1] - 1]);

        sort(ENV.begin() + it, ENV.end());
    }

    XENV.push_back(ENV.size() + 1);
    ENV.push_back(0);
}

bool Is_Neighbours(const size_t i, const size_t j, const std::vector<size_t> &xadj, const std::vector<size_t> &adj) {
    return find(adj.begin() + xadj[i - 1] - 1, adj.begin() + xadj[i] - 1, j) != adj.begin() + xadj[i] - 1;
}

size_t Span_Size(const std::vector<size_t> &xadj, const std::vector<size_t> &adj, size_t &NP) {
    size_t res = 0;

    for (size_t i = 1; i <= NP; ++i)
        for (size_t j = 1; j <= i; ++j)
            if (Is_Neighbours(i, j, xadj, adj))
            {
                res += i - j;
                break;
            }

    return res;
}
