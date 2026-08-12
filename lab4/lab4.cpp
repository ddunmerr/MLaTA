/*
DONE
17.1. Инверсии (4)
Задана некоторая перестановка X = (X 1 , X 2 , …, X N ) чисел от 1 до N. Требуется найти вектор
инверсий и общее количество инверсий в этой перестановке, то есть количество пар чисел (i, j)
таких, что i &lt; j, а X i &gt; X j .
Ввод из файла INPUT.TXT. В первой строке задано число N (1   N  500000). Во второй строке
заданы через пробел элементы перестановки X 1 , X 2 , …, X N .
Вывод в файл OUTPUT.TXT. В первой строке выводится количество инверсий. Во второй
строке – элементы вектора инверсий.
Пример
Ввод
5
2 5 4 1 3
Вывод
6
0 0 1 3 2

ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
*/

#include <fstream>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

std::vector<int> tree;
int n;

int Rsq(int k)
{
	int res = 0;
	while (k > 0)
	{
		res += tree[k];
		k -= k & -k;
	}
	return res;
}

void Add(int k, int d)
{
	while (k <= n)
	{
		tree[k] += d;
		k += k & -k;
	}
}

int main()
{
	std::ifstream fin(INPUT_FILE);
	if (!fin)
	{
		std::cout << "couldnt open input file";
		return 1;
	}
	std::ofstream fout(OUTPUT_FILE);
	if (!fout)
	{
		std::cout << "couldnt open output file";
		return 1;
	}
	
	if (!(fin >> n))
	{
		std::cout << "couldnt read file";
		return 1;
	}

	std::vector<int> vect(n);
	for (int i = 0; i < n; i++)
	{
		fin >> vect[i];
	}

	tree.assign(n + 2, 0);
	long long totalInv = 0;
	std::vector<int> invVector(n);

	for (int i = 0; i < n; i++)
	{
		int greater = Rsq(n) - Rsq(vect[i]);
		invVector[i] = greater;
		totalInv += greater;
		Add(vect[i], 1);
	}

	fout << totalInv << std::endl;
	for (int i = 0; i < n; i++)
	{
		fout << invVector[i];
		if (i != n - 1)
		{
			fout << " ";
		}
	}
	fout << std::endl;

	return 0;
}
