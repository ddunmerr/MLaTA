/*
2.10. Шестеренки (6)
Имеется система сцепленных шестеренок, пронумерованных от 1 до N.
Заданы пары номеров сцепленных шестеренок. Первая должна двигаться по  часовой стрелке. Определить характер движения всех шестеренок.
Варианты движения:
clockwise - по часовой;
unclockwise - против;
immovable - шестеренка неподвижна;
block - заклинивание.
Ввод из файла INPUT.TXT. В первой строке записаны через пробел число N - количество шестеренок (2 ≤ N ≤ 10000)
и M - количество пар (1 ≤ M ≤ 100000). Во следующих M строках указаны пары шестеренок в виде двух номеров через пробел.
Вывод в файл OUTPUT.TXT. В i-й строке должна быть информация о движении i-й шестеренки:
clockwise - по часовой, against - против, immovable – шестеренка неподвижна. Если система заклинивается, то выдать block.
Примеры
Ввод 1       Ввод 2
5 4          5 4
1 2          1 2
2 3          2 3
3 4          1 3
4 1          4 5
Вывод 1      Вывод 2
clockwise    block
unclockwise
clockwise
unclockwise
immovable

ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";
const std::string IMMOVABLE = "immovable";
const std::string CLOCKWISE = "clockwise";
const std::string UNCLOCKWISE = "inclockwise";
const std::string BLOCK = "block";

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

	int N, M;
	fin >> N >> M;

	std::vector<std::vector<int>> graph(N + 1);
	for (int i = 0; i < M; i++)
	{
		int a, b;
		fin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}

	std::vector<int> dir(N + 1, 0); // 0 - не посещена, 1 - clockwise, -1 - unclockwise
	std::queue<int> q;

	dir[1] = 1; // первая по часовой
	q.push(1);

	bool blocked = false;

	while (!q.empty() && !blocked)
	{
		int cur = q.front();
		q.pop();

		for (int next : graph[cur])
		{
			if (dir[next] == 0)
			{
				dir[next] = -dir[cur];
				q.push(next);
			}
			else if (dir[next] == dir[cur])
			{
				blocked = true;
				break;
			}
		}
	}

	if (blocked)
	{
		fout << BLOCK << std::endl;
		return 0;
	}

	for (int i = 1; i <= N; i++)
	{
		if (dir[i] == 0)
		{
			fout << IMMOVABLE << std::endl;
		}
		else if (dir[i] == 1)
		{
			fout << CLOCKWISE << std::endl;
		}
		else
		{
			fout << UNCLOCKWISE << std::endl;
		}
	}

	return 0;
}
