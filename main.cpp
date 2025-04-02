#include "src/include/json/json.h"
#include "src/sparseMethods/MatrixOptimizationMethods.h"
#include "src/sparseMethods/RootLevelMethods.h"
#include "src/sparseMethods/InitialNodeMethods.h"
#include "src/sparseMethods/FileMethods.h"
#include "src/sparseMethods/AdjacencyMethods.h"

#include <iostream>
#include <cassert>


int main()
{
    std::string configPath = "InputData/sparseConfig.json";
    std::ifstream in(configPath, std::ios::in);
    Json::Reader json_reader;
    Json::Value json_root;
    bool read_succeeded = json_reader.parse(in, json_root);
    assert(read_succeeded);

    // инициализация рабочих переменных
    size_t NP = 0; // Количество узлов
    size_t NE = 0; // Количество элементов
    size_t NC = 0; // Количество контуров

    size_t elem_t = 0; // Тип элемента

    std::vector<size_t> Elem;   // Массив элементов
    std::vector<double> Points; // Массив точек
    std::vector<size_t> Cont;   // Массив узлов на контуре

    std::vector<int> HEAD;    // Массивы для
    std::vector<size_t> NBRS; // динамической
    std::vector<int> LINK;    // матрицы

    std::vector<size_t> XADJ; // Массивы для статической
    std::vector<size_t> ADJ;  // матрицы смежности

    std::vector<size_t> RCM;  // Вектор перестановки
    std::vector<size_t> IRCM; // Вектор обратной перестановки

    std::vector<size_t> XENV; // Новые массивы для
    std::vector<size_t> ENV;  // статической матрицы смежности

    std::string meshFileName = json_root.get("meshFileName", "").asString();
    std::string matrixOutputFile = json_root.get("matrixOutputFile", "").asString();
    std::string levelStructureOutputFile = json_root.get("levelStructureOutputFile", "").asString();
    std::string renumberedOutputFile = json_root.get("renumberedOutputFile", "").asString();
    std::string renumberedMeshOutputFile = json_root.get("renumberedMeshOutputFile", "").asString();

    Read_File(meshFileName, NP,NE,NC,elem_t, Elem,Points,Cont);

	Dynamic_Matrix(HEAD, NBRS, LINK, NP, NE,elem_t, Elem);

	Static_Matrix(HEAD, XADJ, ADJ, NBRS, LINK,NP);

	Write_File_Matrices(matrixOutputFile, HEAD, NBRS, LINK,NP,XADJ,ADJ);

	Write_File_Level_Structure(1, levelStructureOutputFile, XADJ, ADJ, NP);

	size_t pseudo = Find_Initial_Node(NP, XADJ, ADJ);

	std::cout << "Pseudo-peripheral node: " << pseudo << std::endl;

	Write_File_Level_Structure(pseudo, levelStructureOutputFile, XADJ, ADJ, NP);

	Reverse_Cuthill_Mckey(NP,XADJ,ADJ,RCM,IRCM,XENV,ENV);

	Write_File_Renumbered(renumberedOutputFile, RCM,IRCM,NP,XENV,ENV);

	Write_File_Renumbered_Mesh(renumberedMeshOutputFile,NP,NE,NC,elem_t, Elem,Points,Cont,RCM,IRCM);

	std::cout << "Span size before renumbering: " << Span_Size(XADJ, ADJ, NP) << std::endl;

    std::cout << "Span size after renumbering: " << Span_Size(XENV, ENV, NP) << std::endl;

	return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.