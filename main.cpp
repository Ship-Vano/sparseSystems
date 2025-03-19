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

// Перегрузка оператора "cout" для vector
template<typename T>
ostream& operator<<(ostream& str, const vector<T>& vec)
{
	for (auto& w : vec)
		str << w << "  ";

	return str;
};

// Процедура чтения из файла
void Read_File(const string& file)
{
	ifstream Fin(file);

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
}

// Добавление ребра i -> j
void Dynamic_Add(const size_t i, const size_t j)
{
	LINK.push_back((int)HEAD[i - 1]);
	NBRS.push_back(j);
	HEAD[i - 1] = int(NBRS.size());
}

// Проверка наличия ребра i -> j
bool Dynamic_Check(const size_t i, const size_t j)
{
	size_t k = 0;

	if (HEAD[i - 1] < 0)
		return 0;

	k = HEAD[i - 1] - 1;

	while (NBRS[k] != j && LINK[k] > 0)
		k = LINK[k] - 1;

	return (NBRS[k] == j);
}

// Процедура построения динамической матрицы смежности
void Dynamic_Matrix()
{
	HEAD.resize(NP, -1);

	size_t curr_i = 0;
	size_t curr_j = 0;

	for (size_t i = 0; i < NE; ++i)
	{
		for (size_t j = 0; j < elem_t; ++j)
			for (size_t k = j + 1; k < elem_t; ++k)
			{
				curr_i = Elem[elem_t * i + j];
				curr_j = Elem[elem_t * i + k];

				if (!Dynamic_Check(curr_i, curr_j))
				{
					Dynamic_Add(curr_i, curr_j);
					Dynamic_Add(curr_j, curr_i);
				}
			}
	}
}

// Процедура построения статической матрицы смежности
void Static_Matrix()
{
	int k = 0;

	size_t it = 0;

	for (size_t i = 0; i < NP; ++i)
	{
		k = HEAD[i] - 1;
		XADJ.push_back(ADJ.size() + 1);

		it = ADJ.size();

		while (k > -1)
		{
			ADJ.push_back(NBRS[k]);
			k = LINK[k] - 1;
		}

		sort(ADJ.begin() + it, ADJ.end());
	}

	XADJ.push_back(ADJ.size() + 1);
	ADJ.push_back(0);
}

// Процедура записи в файл
void Write_File_Matrices(const string& file)
{
	ofstream Fout(file);

	Fout << "Dynamic matrix: \n" << HEAD << "\n" << NBRS << "\n" << LINK << "\n \n";
	Fout << "Static  matrix: \n";

	for (size_t i = 1; i <= NP + 1; ++i)
		Fout << i << "  ";

	Fout << "\n" << XADJ << "\n" << ADJ << "\n";

	Fout.close();
}

// Сравнение количества соседей
bool cmp(const size_t i, const size_t j)
{
	return XADJ[i] - XADJ[i - 1] < XADJ[j] - XADJ[j - 1];
}

// Функция построения корневой структуры уровней
vector<vector<size_t>> Level_Structure(size_t root)
{
	vector<bool> exist(NP, true);
	vector<vector<size_t>> res;
	vector<size_t> prev;
	vector<size_t> cur;

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

		sort(cur.begin(), cur.end(), cmp);

		res.push_back(cur);
		prev = cur;
	}

	return res;
}

// Функция записи корневой структуры уровней в файл
void Write_File_Level_Structure(size_t root, string file)
{
	ofstream Fout(file);

	vector<vector<size_t>> res = Level_Structure(root);

	Fout << "Level structure : \n";

	for (const auto& w : res)
		Fout << w << "\n";

	Fout.close();
}

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

// Функция записи векторов перенумерации и новой статической матрицы смежности
void Write_File_Renumbered(string file)
{
	ofstream Fout(file);

	Fout << "RCM:  " << RCM << "\n" << "IRCM: " << IRCM << "\n \n";

	Fout << "New static matrix: \n";

	for (size_t i = 1; i <= NP + 1; ++i)
		Fout << i << "  ";

	Fout << "\n" << XENV << "\n" << ENV << "\n";

	Fout.close();
}

// Функция записи перенумерованной сетки
void Write_File_Renumbered_Mesh(string file)
{
	ofstream Fout(file);

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
	Read_File("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//output_4_2.txt");

	Dynamic_Matrix();

	Static_Matrix();

	Write_File_Matrices("C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//stat_dyn_out.txt");

	Write_File_Level_Structure(1, "C://Users//-//Desktop//свiт//4 курс//РПК//Лабы//Лаб 2-5//level_struct_1_out.txt");

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