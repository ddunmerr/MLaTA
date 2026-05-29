/*
14.2. Произведение (5)
Среди всех наборов различных целых положительных чисел, сумма которых равна заданному числу N (1 ≤ N ≤ 10000), найдите тот, который имеет максимальное произведение входящих в него чисел.
Ввод из файла INPUT.TXT. В единственной строке вводится N.
Вывод в файл OUTPUT.TXT. В единственной строке выдаются слагаемые через пробел.
Примеры
Ввод 1      Ввод 2
8           100
Вывод 1     Вывод 2
3 5         2 3 5 6 7 8 9 10 11 12 13 14


ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
*/

#include <fstream>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

int main()
{
	std::ifstream fin(INPUT_FILE);
	std::ofstream fout(OUTPUT_FILE);
	int N;
	fin >> N;

	if (N == 1)
	{
		fout << 1 << std::endl;
		return 0;
	}

	std::vector<int> parts;
	int sum = 0;
	int next = 2;
	while (sum + next <= N)
	{
		parts.push_back(next);
		sum += next;
		++next;
	}
	int remains = N - sum;

	int idx = parts.size() - 1;
	while (remains > 0)
	{
		parts[idx]++;
		--remains;
		--idx;
		if (idx < 0)
			idx = parts.size() - 1;
	}

	for (size_t i = 0; i < parts.size(); ++i)
	{
		if (i > 0)
			fout << " ";
		fout << parts[i];
	}
	fout << std::endl;
	return 0;
}
