/*
10.10. Лифт (9)
Высокое здание, состоящее из N этажей (1 ≤ N ≤ 100), оснащено одним лифтом. Этажи пронумерованы от 1 до N снизу вверх. Парковка находится на нулевом этаже, то есть на один этаж ниже первого. На каждом этаже i-ом этаже находится  Ai (0 ≤ Ai ≤ 109) человек. Известно, что лифт не может перевозить более C человек одновременно (1 ≤ C ≤ 109). На преодоление расстояния в один этаж (вверх или вниз)  требуется P секунд (1 ≤ P ≤ 109). Какое наибольшее количество человек лифт может перевезти на парковку за T секунд (0 ≤ T ≤ 109), если изначально он находился на уровне парковки?
Ввод. В первой строке входного файла содержатся целые числа N,  C,  P,  T. Вторая строка содержит последовательность N целых чисел A1, A2,…, AN, разделенных пробелом.
Вывод. В единственной строке выходного файла должно содержаться наибольшее количество человек, которое лифт успеет перевезти на парковку.
Примеры
Ввод 1         Ввод 2
4 5 2 15       4 5 2 18
0 1 2 3        0 1 2 3
Вывод 1        Вывод 2
3              5

ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
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

	long long N, C, P, T;
	fin >> N >> C >> P >> T;

	std::vector<long long> A(N);
	for (int i = 0; i < N; ++i)
	{
		fin >> A[i];
	}

	// префиксные суммы людей на этажах 1..i
	std::vector<long long> pref(N + 1, 0);
	for (int i = 0; i < N; ++i)
	{
		pref[i + 1] = pref[i] + A[i];
	}
	long long total_people = pref[N];

	// проверяет, можно ли перевезти X людей за время не более T
	auto feasible = [&](long long X) -> bool {
		long long total_cur = 0;
		long long max_cur = T / (2 * P); // максимально допустимая сумма ceil
		for (int i = 1; i <= N; ++i)
		{
			long long D = X - pref[i - 1];
			if (D <= 0)
				break;
			total_cur += (D + C - 1) / C;
			if (total_cur > max_cur)
				return false;
		}
		return total_cur <= max_cur;
	};

	long long low = 0, high = total_people, ans = 0;
	while (low <= high)
	{
		long long mid = low + (high - low) / 2;
		if (feasible(mid))
		{
			ans = mid;
			low = mid + 1;
		}
		else
		{
			high = mid - 1;
		}
	}

	fout << ans << std::endl;
	return 0;
}
