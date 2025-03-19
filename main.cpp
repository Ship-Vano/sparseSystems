#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

size_t NP = 0; // Количество узлов
size_t NE = 0; // Количество элементов
size_t NC = 0; // Количество контуров

size_t elem_t = 0; // Тип элемента

vector<size_t> Elem;   // Массив элементов
vector<double> Points; // Массив точек
vector<size_t> Cont;   // Массив узлов на контуре

vector<int> HEAD;    // Массивы для
vector<size_t> NBRS; // динамической
vector<int> LINK;    // матрицы

vector<size_t> XADJ; // Массивы для статической
vector<size_t> ADJ;  // матрицы смежности

vector<size_t> RCM;  // Вектор перестановки
vector<size_t> IRCM; // Вектор обратной перестановки

vector<size_t> XENV; // Новые массивы для
vector<size_t> ENV;  // статической матрицы смежности








// Функция проверки ребра i <-> j
bool Is_Neighbours(const size_t i, const size_t j, const vector<size_t>& xadj, const vector<size_t>& adj)
{
	return find(adj.begin() + xadj[i - 1] - 1, adj.begin() + xadj[i] - 1, j) != adj.begin() + xadj[i] - 1;
}

// Функция вычисления размера оболочки
size_t Span_Size(const vector<size_t>& xadj, const vector<size_t>& adj)
{
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

int main()
{
	//Read_File("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//output_4_2.txt");

	//Dynamic_Matrix();

	//Static_Matrix();

	//Write_File_Matrices("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//stat_dyn_out.txt");

	//Write_File_Level_Structure(1, "C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//level_struct_1_out.txt");

	//cout << "Pseudo-peripheral node: " << Find_Initial_Node() << "\n";

	//Reverse_Cuthill_Mckey();

	//Write_File_Renumbered("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//new_stat_out.txt");

	//Write_File_Renumbered_Mesh("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//new_mesh_out.txt");

	cout << "Span size before renumbering: " << Span_Size(XADJ, ADJ) << "\n";

	cout << "Span size after renumbering: " << Span_Size(XENV, ENV) << "\n";

	return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.