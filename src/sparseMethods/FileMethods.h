#ifndef SPARSESYSTEMS_FILEMETHODS_H
#define SPARSESYSTEMS_FILEMETHODS_H

/*Методы для чтения параметров для ЛР из файлов*/
//TODO: вынести имплементации в .cpp файл, а здесь оставить только объявления

#include "RootLevelMethods.h"

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
                std::vector<size_t>& Elem, std::vector<double>& Points, std::vector<size_t>& Cont);


/** Запись матрицы в файл (ЛР2)
 *
 * @param filePath  - путь до файла
 * @param HEAD      - массив для динамической матрицы
 * @param NBRS      - массив для динамической матрицы
 * @param LINK      - массив для динамической матрицы
 * @param NP        - количество узлов
 * @param XADJ      - массив для статической матрицы
 * @param ADJ       - массив для статической матрицы
 *
 * @return true - если успех, false - если ошибка
 */
bool Write_File_Matrices(const std::string& filePath, const std::vector<int>& HEAD, \
                        const std::vector<size_t>& NBRS, const std::vector<int>& LINK, const size_t& NP,\
                        const std::vector<size_t>& XADJ, const std::vector<size_t> &ADJ);

/** Запись  корневой структуры уровней в файл (ЛР3)
 *
 * @param root      - корневой элемент
 * @param filePath  - путь до файла
 * @param XADJ      - массив для статической матрицы
 * @param ADJ       - массив для статической матрицы
 * @param NP        - количество узлов
 *
 * @return true - если успех, false - если ошибка
 */
bool Write_File_Level_Structure(size_t root, std::string filePath, std::vector<size_t>& XADJ, std::vector<size_t>& ADJ, size_t& NP);

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
                            size_t& NP, std::vector<size_t>& XENV, std::vector<size_t>& ENV);

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
                                std::vector<size_t>& Cont, std::vector<size_t>& RCM, std::vector<size_t>& IRCM);

#endif //SPARSESYSTEMS_FILEMETHODS_H
