/* ### ЛАБОРАТОРНАЯ РАБОТА №3 ### */

#include "Functions.h"       // Функции лабораторной работы
#include "../include/json/json.h"
#include <cassert>
int main() {

    int NP = 0; // Количество точек (2 - прямая, 4 - плоскость)
    int NE1 = 0; // Количество элементов
    int NE2 = 0; // на линии
    int type = 0; // Тип элемента

    std::string configPath = "InputData/meshConfig.json";
    std::ifstream in(configPath, std::ios::in);
    Json::Reader json_reader;
    Json::Value json_root;
    bool read_succeeded = json_reader.parse(in, json_root);
    assert(read_succeeded);

    std::string INPUT_FILEPATH = json_root.get("inputFile", "").asString();

    std::string OUTPUT_FILEPATH = json_root.get("outputFile", "").asString();

    std::vector<std::vector<double>> Points = My_Read_File(INPUT_FILEPATH, NP, NE1, NE2, type);

    if (NP == 2) {
        /* Cетка на Отрезке (1D) */
        My_Write_File_2(Points, OUTPUT_FILEPATH, NP, NE1, type);

    } else if (NP == 4) {
        /* Cетка на Плоскости (2D) */
        //My_Write_File_4(Points, OUTPUT_FILEPATH, NP, NE1, NE2, type);
        My_Write_File_4(Points, OUTPUT_FILEPATH, NP, NE1, NE2, type);

    }

    std::cout <<  "[LOG]: " << "Complete!" << std::endl;
    return EXIT_SUCCESS;
}
