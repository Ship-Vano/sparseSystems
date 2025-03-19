#include "RootLevelMethods.h"

std::vector<std::vector<size_t>>
Level_Structure(size_t &root, std::vector<size_t> &XADJ, std::vector<size_t> &ADJ, size_t &NP) {
    std::vector<bool> exist(NP, true);
    std::vector<std::vector<size_t>> res;
    std::vector<size_t> prev;
    std::vector<size_t> cur;

    prev.push_back(root);
    res.push_back(prev);

    size_t n = 1;
    exist[root - 1] = false;

    while (n < NP)
    {
        cur.resize(0);

        for (const auto& w : prev)
        {
            for (size_t i = XADJ[w - 1] - 1; i < XADJ[w] - 1; ++i)
                if (exist[ADJ[i] - 1])
                {
                    cur.push_back(ADJ[i]);
                    exist[ADJ[i] - 1] = false;
                    ++n;
                }
        }

        std::sort(cur.begin(), cur.end(), Comparator(XADJ));

        res.push_back(cur);
        prev = cur;
    }

    return res;
}
