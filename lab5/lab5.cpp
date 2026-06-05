/*
3.2. Робот 1 (5). Робот находится на расстоянии X шагов от цели.
За один ход он продвигается либо к цели, либо в противоположном направлении.
Если он достигает цели, то немедленно останавливается. Найти количество способов достижения цели ровно за Y шагов.
Ввод из файла INPUT.TXT. В единственной строке находятся X и Y (1 ≤ X, Y ≤ 50).
Вывод в файл OUTPUT.TXT. В единственной строке вывести количество способов достижения цели.
Пример
Ввод 1     Ввод 2
3 3        3 5
Вывод 1    Вывод 2
1          4

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

	int X, Y;
	fin >> X >> Y;

	std::vector<std::vector<int>> ways(X + Y + 2, std::vector<int>(Y + 1, 0));

	ways[0][0] = 1;

	for (int y = 1; y <= Y; y++)
	{
		for (int x = 0; x <= X + Y; x++)
		{
			if (x > 0)
			{
				ways[x][y] += ways[x - 1][y - 1];
			}
			ways[x][y] += ways[x + 1][y - 1];
		}
	}

	fout << ways[X][Y] << std::endl;

	return 0;
}
