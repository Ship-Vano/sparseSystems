#include "FileMethods.h"

bool Read_File(const std::string& filePath, size_t& NP, size_t& NE, size_t& NC, size_t& elem_t, \
                std::vector<size_t>& Elem, std::vector<double>& Points, std::vector<size_t>& Cont)
{
    std::ifstream Fin(filePath);

    if(Fin.is_open()){
        size_t buf = 0;

        Fin >> NE >> NP >> NC >> buf >> elem_t;

        Elem.resize(elem_t * NE, 0);
        Points.resize(3 * NP, 0);

        for (size_t j = 0; j < elem_t; ++j)
            Fin >> Elem[j];

        for (size_t i = 1; i < NE; ++i)
        {
            Fin >> buf >> buf;
            for (size_t j = 0; j < elem_t; ++j)
                Fin >> Elem[elem_t * i + j];
        }

        for (size_t i = 0; i < NP; ++i)
            Fin >> buf >> Points[3 * i] >> Points[3 * i + 1] >> Points[3 * i + 2];

        Fin >> buf;

        Cont.resize(buf, 0);

        for (size_t i = 0; i < buf; ++i)
            Fin >> Cont[i];

        Fin.close();

        return true;
    }
    return false;
}

bool Write_File_Matrices(const std::string &filePath, const std::vector<int> &HEAD, const std::vector<size_t> &NBRS,
                         const std::vector<int> &LINK, const size_t &NP, const std::vector<size_t> &XADJ,
                         const std::vector<size_t> &ADJ) {
    std::ofstream Fout(filePath);
    if(Fout.is_open()){
        Fout << "Dynamic matrix: \n" << HEAD << "\n" << NBRS << "\n" << LINK << "\n \n";
        Fout << "Static  matrix: \n";

        for (size_t i = 1; i <= NP + 1; ++i)
            Fout << i << "  ";

        Fout << "\n" << XADJ << "\n" << ADJ << "\n";

        Fout.close();
        return true;
    }
    return false;
}

bool Write_File_Level_Structure(size_t root, std::string filePath, std::vector<size_t> &XADJ, std::vector<size_t> &ADJ,
                                size_t &NP) {
    std::ofstream Fout(filePath);
    if(Fout.is_open()){
        std::vector<std::vector<size_t>> res = Level_Structure(root, XADJ, ADJ, NP);

        Fout << "Level structure : \n";

        for (const auto& w : res)
            Fout << w << "\n";

        Fout.close();
        return true;
    }
    return false;
}

bool Write_File_Renumbered(std::string filePath, std::vector<size_t> &RCM, std::vector<size_t> &IRCM, size_t &NP,
                           std::vector<size_t> &XENV, std::vector<size_t> &ENV) {
    std::ofstream Fout(filePath);
    if(Fout.is_open()) {
        Fout << "RCM:  " << RCM << "\n" << "IRCM: " << IRCM << "\n \n";

        Fout << "New static matrix: \n";

        for (size_t i = 1; i <= NP + 1; ++i)
            Fout << i << "  ";

        Fout << "\n" << XENV << "\n" << ENV << "\n";
        Fout.close();
        return true;
    }
    return false;

}

bool Write_File_Renumbered_Mesh(std::string filePath, size_t &NP, size_t &NE, size_t &NC, size_t &elem_t,
                                std::vector<size_t> &Elem, std::vector<double> &Points, std::vector<size_t> &Cont,
                                std::vector<size_t> &RCM, std::vector<size_t> &IRCM) {
    std::ofstream Fout(filePath);
    if(Fout.is_open()){
        Fout << NE << " " << NP << " " << NC << "\n";

        for (size_t i = 0; i < NE; ++i)
        {
            Fout << i + 1 << " " << elem_t << " ";

            for (size_t j = 0; j < elem_t; ++j)
                Fout << IRCM[Elem[elem_t * i + j] - 1] << " ";

            Fout << "\n";
        }

        size_t it = 0;

        for (const auto& w : RCM)
            Fout << ++it << " " << Points[3 * (w - 1)] << " " << Points[3 * (w - 1) + 1] << " " << Points[3 * (w - 1) + 2] << "\n";

        Fout << Cont.size() << "\n";

        for (const auto& w : Cont)
            Fout << IRCM[w - 1] << "\n";

        Fout.close();

        return true;
    }
    return false;
}
