/*
19.13. Шахматная доска (3)
Аня разделила доску размера m × n на клетки размера 1 × 1 и раскрасила их в черный и белый цвет в шахматном порядке.
Васю заинтересовал вопрос: клеток какого цвета получилось больше: черного или белого.
Для того чтобы выяснить это, он спросил у Ани, в какой цвет она раскрасила j-ю клетку в i-м ряду доски.
По этой информации Вася попытался определить, клеток какого цвета на доске больше.
Требуется написать программу, которая по размерам доски и цвету j-й клетки в i-м ряду определит, клеток какого цвета на доске больше — черного или белого.

Ввод из файла INPUT.TXT. В единственной строке содержится пять целых чисел: m, n, i, j и c (1 ≤ m, n ≤ 109, 1 ≤ i ≤ m, 1 ≤ j ≤ n, с = 0 или с = 1).
Значение c = 0 означает, что j-я клетка в i-м ряду доски раскрашена в черный цвет, а значение c = 1 - в белый цвет.
Вывод в файл OUTPUT.TXT. В единственной строке выводится одно из трех слов:
black - если черных клеток на доске больше; white - если белых клеток на доске больше, equal - если черных и белых клеток на доске поровну.
наименьшая возможная длина первоначальной последовательности.
Примеры
Ввод 1          Ввод 2          Ввод 3
3 5 1 1 0       3 5 2 1 0      4 4 1 1 1
Вывод 1         Вывод 2        Вывод 2
black            white         equal


ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
*/

#include <fstream>
#include <iostream>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";
const std::string BLACK = "black";
const std::string WHITE = "white";
const std::string EQUAL = "equal";

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

	long long m, n, i, j, c;

	if (!(fin >> m >> n >> i >> j >> c))
	{
		std::cout << "couldnt read file";
		return 1;
	}

	long long total = m * n;
	if (total % 2 == 0)
	{
		fout << EQUAL << std::endl;
		return 0;
	}

	long long black = (total + 1) / 2;
	long long white = total / 2;

	bool isEven = ((i + j) % 2 == 0);

	if ((c == 0 && !isEven) || (c == 1 && isEven))
	{
		std::swap(black, white);
	}

	if (black > white)
	{
		fout << BLACK << std::endl;
	}
	else
	{
		fout << WHITE << std::endl;
	}

	return 0;
}
