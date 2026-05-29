/*
15.2. Спички (4)
Вася и Петя любят следующую игру. Два игрока поочередно забирают из кучки, содержащей N спичек,
либо A, либо B спичек (1 ≤ A, B ≤ N ≤ 105). Игрок проигрывает, если необходимого для хода количества спичек не оказывается.
Игру начинает Вася. Кто выиграет при правильной игре с обеих сторон?
Ввод из файла INPUT.TXT. В единственной строке содержатся значения N, A, B.
Вывод в файл OUTPUT.TXT. В единственной строке выводится значение 1, если выигрывает Вася, либо 2 в случае выигрыша Пети.
Примеры
Ввод 1          Ввод 2
14 3 5          15 2 1
Вывод 1         Вывод 2
1               2

ФИО: Ильин Константин Сергеевич
Группа: ПС-22
Среда разработки: Visual Studio 22
*/

#include <fstream>
#include <iostream>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

int main()
{
	std::ifstream fin(INPUT_FILE);
	std::ofstream fout(OUTPUT_FILE);

	int N, A, B;
	fin >> N >> A >> B;

	std::vector<bool> win(N + 1, false);
	for (int i = 1; i <= N; i++)
	{
		if (i >= A && !win[i - A])
		{
			win[i] = true;
		}
		else if (i >= B && !win[i - B])
		{
			win[i] = true;
		}
		else
		{
			win[i] = false;
		}
	}

	if (win[N])
	{
		fout << 1 << std::endl;
	}
	else
	{
		fout << 2 << std::endl;
	}
	return 0;
}
