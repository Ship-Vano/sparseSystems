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

    std::cout << "Level structire check" << std::endl;
    while (n < NP)
    {
        cur.clear();
        for (const auto& w : prev)
        {
            int tmp_count = 0;
            std::cout << "----" << std::endl;
            int last_size = cur.size();
            std::cout << "last_size = " << last_size << std::endl;
            for (size_t i = XADJ[w - 1] - 1; i < XADJ[w] - 1; ++i) {
                if (exist[ADJ[i] - 1])
                {
                    cur.push_back(ADJ[i]);
                    exist[ADJ[i] - 1] = false;
                    ++n;
                    ++tmp_count;
                }
            }
            if(!tmp_count) {
                continue;
            }
            for (const auto el: cur) {
                std::cout << el << " ";
            }
            std::cout << " - all before sort" << std::endl;
            std::cout << *(cur.begin()+last_size) << " - i will start with it"<< std::endl;
            for (auto it = cur.begin() + last_size; it != cur.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << " - i will sort them"<<std::endl;
            std::sort(cur.begin()+last_size, cur.end(), Comparator(XADJ));
            for (const auto el: cur) {
                std::cout << el << " ";
            }
            std::cout << " - after sort" << std::endl;
            //count += cur.size();

        }

        // std::sort(cur.begin(), cur.end(), Comparator(XADJ));

        res.push_back(cur);
        prev = cur;
    }

    return res;
}
