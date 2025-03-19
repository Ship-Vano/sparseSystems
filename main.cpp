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












// Функция поиска начального узла
size_t Find_Initial_Node()
{
	size_t res = 1;
	size_t buf = 1;
	size_t prev_size = 0;
	size_t prev_nbrs = 0;
	size_t degree = 0;
	size_t min_degree = NP;

	vector<vector<size_t>> lev_struct;

	do
	{
		res = buf;

		lev_struct = Level_Structure(res);

		min_degree = NP;
		prev_size = lev_struct.size();
		prev_nbrs = lev_struct.back().size();

		for (const auto& w : lev_struct.back())
		{
			degree = XADJ[w] - XADJ[w - 1];

			if (degree < min_degree)
			{
				min_degree = degree;
				buf = w;
			}
		}

		lev_struct = Level_Structure(buf);
	} while (lev_struct.size() > prev_size || lev_struct.back().size() > prev_nbrs);

	return res;
}

// Сравнение старых номеров узлов
bool cmp_RCM(const vector<size_t>& v1, const vector<size_t>& v2)
{
	return v1[1] < v2[1];
}

// Алгоритм Картхелла-Макки
void Reverse_Cuthill_Mckey()
{
	size_t root = Find_Initial_Node();

	vector<vector<size_t>> lev_struct = Level_Structure(root);

	for (const auto& u : lev_struct)
		for (const auto& w : u)
			RCM.push_back(w);

	vector<vector<size_t>> permutation;

	vector<size_t> buf(2, 0);

	for (size_t i = 1; i <= NP; ++i)
	{
		buf = { i, RCM[i - 1] };
		permutation.push_back(buf);
	}

	sort(permutation.begin(), permutation.end(), cmp_RCM);

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

	cout << "Pseudo-peripheral node: " << Find_Initial_Node() << "\n";

	Reverse_Cuthill_Mckey();

	Write_File_Renumbered("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//new_stat_out.txt");

	Write_File_Renumbered_Mesh("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//new_mesh_out.txt");

	cout << "Span size before renumbering: " << Span_Size(XADJ, ADJ) << "\n";

	cout << "Span size after renumbering: " << Span_Size(XENV, ENV) << "\n";

	return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.