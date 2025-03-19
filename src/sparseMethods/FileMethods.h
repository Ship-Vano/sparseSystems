#ifndef SPARSESYSTEMS_FILEMETHODS_H
#define SPARSESYSTEMS_FILEMETHODS_H

/*Методы для чтения параметров для ЛР из файлов*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include <fstream>
#include <vector>

// Перегрузка оператора "cout" для vector
template<typename T>
std::ostream& operator<<(std::ostream& str, const std::vector<T>& vec)
{
    for (auto& w : vec)
        str << w << "  ";

    return str;
};

/** Чтение сетки из файла (ЛР2)
 *
 * @param filePath  - путь до файла
 * @param NP        - количество узлов
 * @param NE        - количество элементов
 * @param NС        - количество контуров
 * @param elem_t    - тип элемента
 * @param Elem      - массив элементов
 * @param Points    - массив точек
 * @param Cont      - массив узлов на контуре
 *
 * @return true - если успех, false - если ошибка
 */
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


/** Запись векторов перенумерации и новой статической матрицы смежности (ЛР5)
 *
 * @param filePath  - путь до файла
 * @param RCM       - Вектор перестановки
 * @param IRCM      - Вектор обратной перестановки
 * @param NP        - количество узлов
 * @param XENV      - Новый массив для статической матрицы жёсткости (1)
 * @param ENV      - Новый массив для статической матрицы жёсткости (2)
 *
 * @return true - если успех, false - если ошибка
 */
bool Write_File_Renumbered(std::string filePath, std::vector<size_t>& RCM, std::vector<size_t>& IRCM,\
                            size_t& NP, std::vector<size_t>& XENV, std::vector<size_t>& ENV)
{
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

/** Запись перенумерованной сетки (ЛР5)
 *
 * @param filePath  - путь до файла
 * @param NP        - количество узлов
 * @param NE        - количество элементов
 * @param NС        - количество контуров
 * @param elem_t    - тип элемента
 * @param Elem      - массив элементов
 * @param Points    - массив точек
 * @param Cont      - массив узлов на контуре
 * @param RCM       - Вектор перестановки
 * @param IRCM      - Вектор обратной перестановки
 *
 * @return true - если успех, false - если ошибка
 */
bool Write_File_Renumbered_Mesh(std::string filePath, size_t& NP, size_t& NE, size_t& NC,\
                                size_t& elem_t, std::vector<size_t>& Elem, std::vector<double>& Points,\
                                std::vector<size_t>& Cont, std::vector<size_t>& RCM, std::vector<size_t>& IRCM)
{
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

#endif //SPARSESYSTEMS_FILEMETHODS_H
