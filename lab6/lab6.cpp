/*
11.1. А у нас в квартире газ (6)
В некотором районе проводится всеобщая газификация.
Для этого прежде всего нужно построить газораспределительную станцию.
Она может располагаться только на участке магистрального газопровода, соединяющего по прямой пункты A и B.
На карте района известны координаты этих пунктов (u1, v1) и (u2, v2) соответственно.
От станции протягиваются отдельные прямолинейные трубы к N (N ≤ 100) населенным пунктам c координатами (xi, yi) (-100 ≤ xi, yi  ≤ 100).
Известно, что затраты на проведение газовой трубы равны квадрату длины трубы. Требуется указать такие координаты газораспределительной
станции, чтобы общие затраты на трубы были минимальны.
Ввод из файла INPUT.TXT. В первой строке задается значения N. Во второй строке указываются через пробел u1, v1, u2, v2.
В следующих N строках задаются через пробел координаты xi,  yi  населенных пунктов.
Вывод в файл OUTPUT.TXT. Вывести с десятью знаками после запятой: в первой строке координаты станции, 
во второй строке минимальную стоимость труб.
Пример
Ввод
2
0 0 4 4
1 1
3 3
Вывод
2.0000000000 2.0000000000
4.0000000000

ФИО: Ильин Консатнтин Сергеевич
Группа: ПС-22
Среда выполнения: Visual Studio 2026
*/

#include <fstream>
#include <iomanip>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

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
	int n;
	if (!(fin >> n))
	{
		std::cout << "couldnt read" << std::endl;
		return 1;
	}
	double u1, v1, u2, v2;
	if (!(fin >> u1 >> v1 >> u2 >> v2))
	{
		std::cout << "couldnt read" << std::endl;
		return 1;
	}

	std::vector<double> x(n), y(n);
	for (int i = 0; i < n; i++)
	{
		if (!(fin >> x[i] >> y[i]))
		{
			std::cout << "couldnt read" << std::endl;
			return 1;
		}
	}

	// Вектор направления отрезка AB
	double Vx = u2 - u1;
	double Vy = v2 - v1;

	// F(t) = Σ|P(t) - p_i|²
	// F(t) = αt² + βt + γ
	// α = n·(V,V) = n·(Vx² + Vy²)                — коэффициент при t²
    // β = 2·Σ_i (d_i,V),  d_i = A - p_i          — коэффициент при t
    // γ = Σ_i (d_i,d_i) = Σ_i (dx² + dy²)        — свободный член
	double alpha = n * (Vx * Vx + Vy * Vy);
	double beta = 0.0;
	double gamma = 0.0;

	for (int i = 0; i < n; i++)
	{
		 // d_i = A - p_i  - вектор от i-го пункта к точке A
        // dx, dy — компоненты вектора d_i
		double dx = u1 - x[i];
		double dy = v1 - y[i];

		// β += 2·(d_i, V) = 2·(dx·Vx + dy·Vy)
        //     (d_i, V) - скалярное произведение векторов d_i и V
		beta += 2.0 * (dx * Vx + dy * Vy);

		// γ += (d_i, d_i) = dx² + dy²
		gamma += dx * dx + dy * dy;
	}

	// Поиск минимума параболы F(t) = αt² + βt + γ
    // Вершина параболы: t* = -β / (2α)
    // (α > 0, поэтому это точка минимума)
	double t = (-beta / (2.0 * alpha));

	// Так как P(t) = A + t·V должна лежать на отрезке AB,
    // параметр t ограничен: t=0 -> точка A, t=1 -> точка B.
    // Парабола выпуклая вверх, поэтому:
    //   t* < 0  -> минимум на отрезке в t = 0
    //   t* > 1  -> минимум на отрезке в t = 1
    //   иначе   -> минимум в t*
	if (t < 0.0)
	{
		t = 0.0;
	}
	if (t > 1.0)
	{
		t = 1.0;
	}

	// Координаты станции C = A + t·V
    // Cx, Cy - искомые координаты газораспределительной станции
	double Cx = u1 + t * Vx;
	double Cy = v1 + t * Vy;
	double cost = alpha * t * t + beta * t + gamma;

	fout << std::fixed << std::setprecision(10);
	fout << Cx << " " << Cy << std::endl;
	fout << cost << std::endl;

	return 0;
}
