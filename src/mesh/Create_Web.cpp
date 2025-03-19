/*
 * РЕАЛИЗАЦИЯ ФУНКЦИЙ ДЛЯ ПОТРОЕНИЯ СЕТОК
 *
 * */

#include "Functions.h"



/* Функция для Вычисления узла */
// Возвращает точку пересечения диагоналей треугольника
//std::vector<double> My_nodes(const std::vector<double>& v1, const std::vector<double>& v2,
//                             const std::vector<double>& v3, const std::vector<double>& v4) {
//
//    std::vector<double> res(3, 0.0);
//    double t = 0.0;
//
//    double a11 = 0.0, a12 = 0.0, a21 = 0.0, a22 = 0.0, b1 = 0.0, b2 = 0.0;
//
//    a11 = v2[0] - v1[0];
//    a12 = v3[0] - v4[0];
//    a21 = v2[1] - v1[1];
//    a22 = v3[1] - v4[1];
//    b1 = v3[0] - v1[0];
//    b2 = v3[1] - v1[1];
//
//    if (fabs(My_det2(a11, a12, a21, a22)) > EPS)
//        t = My_get_par(a11, a12, a21, a22, b1, b2);
//    else {
//
//        a21 = v2[2] - v1[2];
//        a22 = v3[2] - v4[2];
//        b2 = v3[2] - v1[2];
//
//        if (fabs(My_det2(a11, a12, a21, a22)) > EPS)
//            t = My_get_par(a11, a12, a21, a22, b1, b2);
//        else
//        {
//            a11 = v2[1] - v1[1];
//            a12 = v3[1] - v4[1];
//            b1 = v3[1] - v1[1];
//
//            if (fabs(My_det2(a11, a12, a21, a22)) > EPS)
//                t = My_get_par(a11, a12, a21, a22, b1, b2);
//            else
//                std::cout << "Missing Error! \n";
//        }
//    }
//
//    for (size_t i = 0; i < 3; ++i)
//        res[i] = v1[i] + t * (v2[i] - v1[i]);
//
//    return res;
//}

// Возвращает точку пересечения диагоналей четырехугольника или центр прямой, соединяющей центры диагоналей
std::vector<double> My_nodes(const std::vector<double>& v1, const std::vector<double>& v2,
                             const std::vector<double>& v3, const std::vector<double>& v4) {

    std::vector<double> res(3, 0.0);
    double t = 0.0;

    double a11 = v2[0] - v1[0];
    double a12 = v3[0] - v4[0];
    double a21 = v2[1] - v1[1];
    double a22 = v3[1] - v4[1];
    double b1 = v3[0] - v1[0];
    double b2 = v3[1] - v1[1];

    if (std::abs(My_det2(a11, a12, a21, a22)) > EPS) {
        t = My_get_par(a11, a12, a21, a22, b1, b2);
        for (size_t i = 0; i < 3; ++i)
            res[i] = v1[i] + t * (v2[i] - v1[i]);

    } else {
        // Если диагонали скрещиваются, вычисляем центры диагоналей
        std::vector<double> centerDiag1 = {
                (v1[0] + v3[0]) / 2,
                (v1[1] + v3[1]) / 2,
                (v1[2] + v3[2]) / 2
        };
        std::vector<double> centerDiag2 = {
                (v2[0] + v4[0]) / 2,
                (v2[1] + v4[1]) / 2,
                (v2[2] + v4[2]) / 2
        };

        // Центр прямой, соединяющей центры диагоналей
        for (size_t i = 0; i < 3; ++i)
            res[i] = (centerDiag1[i] + centerDiag2[i]) / 2;
    }

    return res;
}

/* Функция - Построение сетки для отрезка */
bool My_Write_File_2(const std::vector<std::vector<double>>& Points, const std::string& file,
                     const int&  NP, const int& NE1, const int& type) {

    std::ofstream Fout(file);

    if (!Fout.is_open()) {
        std::cout << "[LOG]: " << "File " << file << " is NOT open." << std::endl;
        return false;
    } else {

        // Для линейных элементов
        if (type == 1) {
            // Записываем число элементов, узлов и кол-во контуров
            // NE1 элементов << NE1 + 1 узлов << 2 контура
            Fout << NE1 << " " << NE1 + 1 << " " << 2 << "\n";

            for (size_t i = 1; i <= NE1; ++i)
                // Номер элемента << 2 узла в каждом элементе << номер первого узла << номер второго узла
                Fout << i << " " << 2 << " " << i << " " << i + 1 << "\n";

        } else {
            // Для квадратичный элемент элементов

            // Записываем число элементов, узлов и кол-во контуров
            Fout << NE1 << " " << 2 * NE1 + 1 << " " << 2 << "\n"; // NE1 элементов << 2 * NE1 + 1 узлов << 2 контура

            // Номер элемента << 3 узла в каждом элементе << номер первого узла << номер второго узла
            Fout << 1 << " " << 3 << " " << 1 << " " << 3 << " " << 2 << "\n";

            for (size_t i = 2; i < NE1; ++i)
                Fout << i << " " << 3 << " " << i << " " << i + 3 << " " << i + 2 << "\n";

            Fout << NE1 << " " << 3 << " " << 2 * NE1 - 2 << " " << 2 * NE1 + 1 << " " << 2 * NE1 << "\n";

        }

        std::vector<double> s(3, 0.0); // Направляющий вектор прямой, на которой лежит данных отрезок
        auto bufP = s; // Координаты текущего узла

        double coef = 0.5 / NE1; // Коэффициент для получения вектора, соответствующего одному элементу

        if (type == 1) // Для линейных элементов
            coef *= 2.0;

        bufP = Points[0]; // Первый узел - левый конец отрезка

        for (size_t j = 0; j < 3; ++j)
            s[j] = coef * (Points[1][j] - bufP[j]); // Координаты вектора по двум крайним точкам отрезка

        if (type == 1) // Для линейных элементов
            for (size_t i = 1; i <= NE1 + 1; ++i) {
                // Номер узла << Координаты узла
                Fout << i << " " << bufP << "\n";

                bufP += 2.0 * s; // Переход к следующему узлу
            }
        else // Для квадратичных элементов
        {
            // Запись первого узла
            Fout << 1 << " " << bufP << "\n";

            bufP += 2.0 * s; // Переход ко второму узлу

            // Запись второго узла
            Fout << 2 << " " << bufP << "\n";

            for (size_t i = 3; i <= 2 * NE1 - 1; i += 2) {
                bufP += (-1.0) * s; // Переход к нечётному узлу

                // Номер узла << Координаты узла
                Fout << i << " " << bufP << "\n";

                bufP += 3.0 * s; // Переход к чётному узлу

                // Номер узла << Координаты узла
                Fout << i + 1 << " " << bufP << "\n";
            }

            bufP += (-1.0) * s; // Переход к последнему узлу

            // Запись последнего узла
            Fout << 2 * NE1 + 1 << " " << bufP << "\n";
        }

        Fout << 1 << " " << 1 << "\n"; // Количество узлов на первом и втором контурах(концах отрезка)

        if (type == 1) // Для линейных элементов
            Fout << 1 << "\n" << NE1 + 1; // Номера узлов в первом и втором контурах(концах отрезка)
        else
            Fout << 1 << "\n" << 2 * NE1; // Номера узлов в первом и втором контурах(концах отрезка)

        Fout.close();
    }
    std::cout << "[LOG]: " << "Web2 is done. Web is write in " << file << std::endl;
    return true;
}

/* Функция - Построение сетки для участка плоскости */
//bool My_Write_File_4(const std::vector<std::vector<double>>& Points, const std::string& file,
//                      const int& NP, const int& NE1, const int& NE2, const int& type) {
//
//    std::ofstream Fout(file);
//
//    if (!Fout.is_open()) {
//        std::cout << "[LOG]: " << "File " << file << " is NOT open." << std::endl;
//        return false;
//
//    } else {
//
//        /* Запись кол-ва элементов, узлов, границ */
//        if (type == 1) { // Ризбиение на четырехугольники
//
//            Fout << NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) << " " << 1
//                 << "\n"; // NE1 * NE2 элементов << (NE1 + 1) * (NE2 + 1) узлов << 1 контур
//
//        } else if (type == 2 || type == 3) {// Разбиение на диагонали
//
//            Fout << 2 * NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) << " " << 1
//                 << "\n"; // 2 * NE1 * NE2 элементов << (NE1 + 1) * (NE2 + 1) узлов << 1 контур
//
//        } else if (type == 4) // Для центрального разбиения
//            Fout << 4 * NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) + NE1 * NE2 << " " << 1 << "\n";
//
//
//        /* Нумерация элементов */
//        if (type == 1) {// Для обычного разбиения
//            for (size_t j = 1; j <= NE2; ++j) {
//                for (size_t i = 1; i <= NE1; ++i) {
//
//                    // Номер элемента << 4 узла в каждом элементе << номер первого узла << номер второго узла
//                    Fout << (j - 1) * NE1 + i << " "    << 4 << " "
//                         << (j - 1) * (NE1 + 1) + i     << " "  // 1-й узел
//                         << (j - 1) * (NE1 + 1) + i + 1 << " "  // 2-й узел
//                         << j * (NE1 + 1) + i + 1       << " "  // 3-й узел
//                         << j * (NE1 + 1) + i           << " "  // 4-й узел
//                         << "\n";
//
//                    // Номер третьего узла << номер четвёртого узла
//                    //Fout << j * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i << " " << "\n";
//                }
//            }
//        } else if (type == 2 || type == 3) {// Для диагонального разбиения
//            for (size_t j = 1; j <= NE2; ++j) {
//                for (size_t i = 1; i <= NE1; ++i) {
//                    // Номер элемента << 3 узла в каждом элементе << номер первого узла
//                    Fout << 2 * (j - 1) * NE1 + i   << " " << 3 << " "
//                    << (j - 1) * (NE1 + 1) + i      << " " // 1-й узел
//                    << (j - 1) * (NE1 + 1) + i + 1  << " " // 2-й узел
//                    << j * (NE1 + 1) + i + 3 - type << " " // 3-й узел
//                    << "\n";
//
//                    // Номер второго узла << номер третьего узла
//                    //Fout << (j - 1) * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i + 3 - type << "\n";
//                }
//
//                for (size_t i = NE1 + 1; i <= 2 * NE1; ++i) {
//                    // Номер элемента << 3 узла в каждом элементе << номер первого узла
//                    Fout << 2 * (j - 1) * NE1 + i << " " << 3 << " " << (j - 1) * (NE1 + 1) + i - NE1 + type - 2 << " ";
//
//                    // Номер второго узла << номер третьего узла
//                    Fout << j * (NE1 + 1) + i + 1 - NE1 << " " << j * (NE1 + 1) + i - NE1 << "\n";
//                }
//            }
//        } else if (type == 4) { // Для центрального разбиения
//
//            for (size_t j = 1; j <= NE2; ++j)
//                for (size_t i = 1; i <= NE1; ++i) {
//
//                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 1 << " " << 3 << " " << \
//                    (j - 1) * (NE1 + 1) + i << " " << (j - 1) * (NE1 + 1) + i + 1 << " " << \
//                    (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";
//
//                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 2 << " " << 3 << " " << \
//                        (j - 1) * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i + 1 << " "
//                         << (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";
//
//                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 3 << " " << 3 << " " << \
//                        j * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i << " " << \
//                        (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";
//
//                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 4 << " " << 3 << " " << \
//                        j * (NE1 + 1) + i << " " << (j - 1) * (NE1 + 1) + i << " " << \
//                        (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";
//                }
//        }
//
//        /*---*/
//
//        const double coef1 = 1.0 / NE1; // Вспомогательные
//        const double coef2 = 1.0 / NE2; // коэффициенты
//
//        std::vector<double> s1(3, 0.0); // Направляющий вектор первой
//        auto s2 = s1, s3 = s2, s4 = s2; // Направляющий вектор остальных трёх прямых
//
//        // Вычисление направляющих векторов
//
//        s1 = coef1 * Points[1];
//        s1 += (-1.0 * coef1) * Points[0];
//
//        s2 = coef2 * Points[2];
//        s2 += (-1.0 * coef2) * Points[1];
//
//        s3 = coef1 * Points[2];
//        s3 += (-1.0 * coef1) * Points[3];
//
//        s4 = coef2 * Points[3];
//        s4 += (-1.0 * coef2) * Points[0];
//
//        // Массивы точек на каждой прямой
//        std::vector<std::vector<double>> P12(NE1 + 1);
//        std::vector<std::vector<double>> P23(NE2 + 1);
//        auto P43 = P12, P14 = P23;
//
//        // Пробегаем все точки на каждой прямой
//        for (size_t i = 0; i < NE1 + 1; ++i) {
//            P12[i] = Points[0];
//            P12[i] += double(i) * s1;
//
//            P43[i] = Points[3];
//            P43[i] += double(i) * s3;
//        }
//
//        for (size_t i = 0; i < NE2 + 1; ++i) {
//            P23[i] = Points[1];
//            P23[i] += double(i) * s2;
//
//            P14[i] = Points[0];
//            P14[i] += double(i) * s4;
//        }
//
//
//        std::vector<double> nP(3, 0.0);
//
//        std::vector<std::vector<double>> Pnts; // Массив узлов для типа 4
//
//        // Запись координат узлов для типа 1, 2, 3 и начало 4
//        for (size_t j = 0; j <= NE2; ++j)
//            for (size_t i = 0; i <= NE1; ++i) {
//                nP = My_nodes(P14[j], P23[j], P12[i], P43[i]);
//
//                Fout << j * (NE1 + 1) + i + 1 << " " << nP << "\n";
//
//                if (type == 4)
//                    Pnts.push_back(nP);
//            }
//
//        //продолжение записи координат узлов для типа 4
//        if (type == 4) {
//            for (size_t j = 1; j <= NE2; ++j) {
//                for (size_t i = 1; i <= NE1; ++i) {
//                    nP = My_nodes(
//                                  Pnts[(j - 1) * (NE1 + 1) + i - 1],
//                                  Pnts[ j      * (NE1 + 1) + i],
//                                  Pnts[(j - 1) * (NE1 + 1) + i],
//                                  Pnts[ j      * (NE1 + 1) + i - 1]
//                                  );
//
//                    Fout << (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << " " << nP << "\n";
//                }
//            }
//        }
//
//        Fout << 2 * (NE1 + NE2) << "\n"; // Количество узлов на контуре
//
//        // Номера узлов на контуре
//        for (size_t i = 1; i <= NE1 + 1; ++i)
//            Fout << i << "\n";
//
//        for (size_t i = 2; i <= NE2 + 1; ++i)
//            Fout << i * (NE1 + 1) << "\n";
//
//        for (size_t i = 2; i <= NE1 + 1; ++i)
//            Fout << (NE2 + 1) * (NE1 + 1) - i + 1 << "\n";
//
//        for (size_t i = 1; i < NE2; ++i)
//            Fout << (NE2 - i) * (NE1 + 1) + 1 << "\n";
//
//        Fout.close();
//    }
//    std::cout << "[LOG]: " << "Web4 is done. Web is write in " << file << std::endl;
//    return true;
//}



double N1(double ksi, double eta){
    return 0.25 * (1 - ksi) * (1 - eta);
}
double N2(double ksi, double eta){
    return 0.25 * (1 + ksi) * (1 - eta);
}
double N3(double ksi, double eta){
    return 0.25 * (1 + ksi) * (1 + eta);
}
double N4(double ksi, double eta){
    return 0.25 * (1 - ksi) * (1 + eta);
}

std::vector<double> makeglobal(double ksi, double eta, std::vector<std::vector<double>> points){
    std::vector<double> res(3, 0.0);

    double n1 = N1(ksi, eta);
    double n2 = N2(ksi, eta);
    double n3 = N3(ksi, eta);
    double n4 = N4(ksi, eta);

    res[0] = n1 * points[0][0] + n2 * points[1][0] + n3 * points[2][0] + n4 * points[3][0];
    res[1] = n1 * points[0][1] + n2 * points[1][1] + n3 * points[2][1] + n4 * points[3][1];
    res[2] = n1 * points[0][2] + n2 * points[1][2] + n3 * points[2][2] + n4 * points[3][2];

    return res;
}

bool My_Write_File_4(const std::vector<std::vector<double>>& Points, const std::string& file,
                     const int& NP, const int& NE1, const int& NE2, const int& type) {

    std::ofstream Fout(file);

    if (!Fout.is_open()) {
        std::cout << "[LOG]: " << "File " << file << " is NOT open." << std::endl;
        return false;

    } else {

        /* Запись кол-ва элементов, узлов, границ */
        if (type == 1) { // Ризбиение на четырехугольники

            Fout << NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) << " " << 1
                 << "\n"; // NE1 * NE2 элементов << (NE1 + 1) * (NE2 + 1) узлов << 1 контур

        } else if (type == 2 || type == 3) {// Разбиение на диагонали

            Fout << 2 * NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) << " " << 1
                 << "\n"; // 2 * NE1 * NE2 элементов << (NE1 + 1) * (NE2 + 1) узлов << 1 контур

        } else if (type == 4) // Для центрального разбиения
            Fout << 4 * NE1 * NE2 << " " << (NE1 + 1) * (NE2 + 1) + NE1 * NE2 << " " << 1 << "\n";


        /* Нумерация элементов */
        if (type == 1) {// Для обычного разбиения
            for (size_t j = 1; j <= NE2; ++j) {
                for (size_t i = 1; i <= NE1; ++i) {

                    // Номер элемента << 4 узла в каждом элементе << номер первого узла << номер второго узла
                    Fout << (j - 1) * NE1 + i << " "    << 4 << " "
                         << (j - 1) * (NE1 + 1) + i     << " "  // 1-й узел
                         << (j - 1) * (NE1 + 1) + i + 1 << " "  // 2-й узел
                         << j * (NE1 + 1) + i + 1       << " "  // 3-й узел
                         << j * (NE1 + 1) + i           << " "  // 4-й узел
                         << "\n";

                    // Номер третьего узла << номер четвёртого узла
                    //Fout << j * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i << " " << "\n";
                }
            }
        } else if (type == 2 || type == 3) {// Для диагонального разбиения
            for (size_t j = 1; j <= NE2; ++j) {
                for (size_t i = 1; i <= NE1; ++i) {
                    // Номер элемента << 3 узла в каждом элементе << номер первого узла
                    Fout << 2 * (j - 1) * NE1 + i   << " " << 3 << " "
                         << (j - 1) * (NE1 + 1) + i      << " " // 1-й узел
                         << (j - 1) * (NE1 + 1) + i + 1  << " " // 2-й узел
                         << j * (NE1 + 1) + i + 3 - type << " " // 3-й узел
                         << "\n";

                    // Номер второго узла << номер третьего узла
                    //Fout << (j - 1) * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i + 3 - type << "\n";
                }

                for (size_t i = NE1 + 1; i <= 2 * NE1; ++i) {
                    // Номер элемента << 3 узла в каждом элементе << номер первого узла
                    Fout << 2 * (j - 1) * NE1 + i << " " << 3 << " " << (j - 1) * (NE1 + 1) + i - NE1 + type - 2 << " ";

                    // Номер второго узла << номер третьего узла
                    Fout << j * (NE1 + 1) + i + 1 - NE1 << " " << j * (NE1 + 1) + i - NE1 << "\n";
                }
            }
        } else if (type == 4) { // Для центрального разбиения

            for (size_t j = 1; j <= NE2; ++j)
                for (size_t i = 1; i <= NE1; ++i) {

                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 1 << " " << 3 << " " << \
                    (j - 1) * (NE1 + 1) + i << " " << (j - 1) * (NE1 + 1) + i + 1 << " " << \
                    (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";

                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 2 << " " << 3 << " " << \
                        (j - 1) * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i + 1 << " "
                         << (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";

                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 3 << " " << 3 << " " << \
                        j * (NE1 + 1) + i + 1 << " " << j * (NE1 + 1) + i << " " << \
                        (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";

                    Fout << 4 * (j - 1) * NE1 + 4 * (i - 1) + 4 << " " << 3 << " " << \
                        j * (NE1 + 1) + i << " " << (j - 1) * (NE1 + 1) + i << " " << \
                        (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << "\n";
                }
        }

        /*---*/

        const double coef1 = 1.0 / NE1; // Вспомогательные
        const double coef2 = 1.0 / NE2; // коэффициенты

        std::vector<double> s1(3, 0.0); // Направляющий вектор первой
        auto s2 = s1, s3 = s2, s4 = s2; // Направляющий вектор остальных трёх прямых

        // Вычисление направляющих векторов

        std::vector<std::vector<double>> localPoints = {{-1, -1, 0},
                                                        { 1, -1, 0},
                                                        { 1,  1, 0},
                                                        {-1,  1, 0}};
        s1 = coef1 * localPoints[1];
        s1 += (-1.0 * coef1) * localPoints[0];

        s2 = coef2 * localPoints[2];
        s2 += (-1.0 * coef2) * localPoints[1];

        s3 = coef1 * localPoints[2];
        s3 += (-1.0 * coef1) * localPoints[3];

        s4 = coef2 * localPoints[3];
        s4 += (-1.0 * coef2) * localPoints[0];


        // Массивы точек на каждой прямой local
        std::vector<std::vector<double>> localP12(NE1 + 1);
        std::vector<std::vector<double>> localP23(NE2 + 1);
        auto localP43 = localP12, localP14 = localP23;

        std::vector<std::vector<double>> P12(NE1 + 1);
        std::vector<std::vector<double>> P23(NE2 + 1);
        auto P43 = P12, P14 = P23;


        // Пробегаем все точки на каждой прямой
        for (size_t i = 0; i < NE1 + 1; ++i) {
            localP12[i] = localPoints[0];
            localP12[i] += double(i) * s1;

            localP43[i] = localPoints[3];
            localP43[i] += double(i) * s3;
        }

        for (size_t i = 0; i < NE2 + 1; ++i) {
            localP23[i] = localPoints[1];
            localP23[i] += double(i) * s2;

            localP14[i] = localPoints[0];
            localP14[i] += double(i) * s4;
        }


        std::vector<double> nP(3, 0.0);

        std::vector<std::vector<double>> Pnts; // Массив узлов для типа 4
        std::vector<std::vector<double>> localPnts; // Массив узлов для типа 4

        // Запись координат узлов для типа 1, 2, 3 и начало 4
        for (size_t j = 0; j <= NE2; ++j)
            for (size_t i = 0; i <= NE1; ++i) {
                nP = My_nodes(localP14[j], localP23[j], localP12[i], localP43[i]);

                Fout << j * (NE1 + 1) + i + 1 << " " << makeglobal(nP[0], nP[1], Points) << "\n";

                if (type == 4)
                    localPnts.push_back(nP);
            }

        //продолжение записи координат узлов для типа 4
        if (type == 4) {
            for (size_t j = 1; j <= NE2; ++j) {
                for (size_t i = 1; i <= NE1; ++i) {
                    nP = My_nodes(
                            localPnts[(j - 1) * (NE1 + 1) + i - 1],
                            localPnts[ j      * (NE1 + 1) + i],
                            localPnts[(j - 1) * (NE1 + 1) + i],
                            localPnts[ j      * (NE1 + 1) + i - 1]
                    );

                    Fout << (NE2 + 1) * (NE1 + 1) + (j - 1) * NE1 + i << " " << makeglobal(nP[0], nP[1], Points) << "\n";
                }
            }
        }

        Fout << 2 * (NE1 + NE2) << "\n"; // Количество узлов на контуре

        // Номера узлов на контуре
        for (size_t i = 1; i <= NE1 + 1; ++i)
            Fout << i << "\n";

        for (size_t i = 2; i <= NE2 + 1; ++i)
            Fout << i * (NE1 + 1) << "\n";

        for (size_t i = 2; i <= NE1 + 1; ++i)
            Fout << (NE2 + 1) * (NE1 + 1) - i + 1 << "\n";

        for (size_t i = 1; i < NE2; ++i)
            Fout << (NE2 - i) * (NE1 + 1) + 1 << "\n";

        Fout.close();
    }
    std::cout << "[LOG]: " << "Web4 is done. Web is write in " << file << std::endl;
    return true;
}




