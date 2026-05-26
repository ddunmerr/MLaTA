/*
1.9. Дамба (9)
В рыбохозяйстве "Рыбнастол" принято решение о разведении карасей и щук. К сожалению, эти рыбы не могут быть вместе в одном водоеме,
так как щуки предпочитают питаться исключительно карасями. Планируется каждое из k озер разделить дамбой на две не сообщающиеся друг с другом части.
На карте каждое i-е озеро представлено в определенном масштабе прямоугольным  участком  mi × ni единиц, разбитым на единичные квадраты.
Отдельный квадрат целиком занят водой или сушей. Множество водных квадратов является связным. Это означает, что из любого водного квадрата озера можно попасть в любой другой водный квадрат,
последовательно переходя по водным квадратам через их общую сторону. Такие последовательности связанных квадратов будем называть путями.
Дамба имеет вид непрерывной ломаной, проходящей по сторонам квадратов. Два водных квадрата, общая сторона которых принадлежит ломаной, становятся не сообщающимися напрямую друг с другом.
Требуется для каждого озера определить минимальную по количеству сторон длину дамбы, разделяющей озеро на две не сообщающиеся между собой связные части.
Чтобы обеспечить доступ рыбаков к воде, каждая из двух полученных частей озера должна сообщаться с берегом. Иными словами, каждая часть должна содержать водный квадрат,
который либо сам находится на границе исходного прямоугольного участка, либо имеет общую сторону с квадратом суши, связанным с границей путем из квадратов суши.
  Ввод. В первой строке содержится число k (1 ≤ k ≤ 10). В следующих строках следуют k блоков данных. Каждый блок описывает одно озеро. В первой строке блока содержатся числа mi и ni, разделенные пробелом.
В следующих mi строках находится матрица, представляющая озеро, по ni символов в строке. Символ '.' обозначает квадрат суши, а символ '#' – квадрат воды.
Гарантируется наличие не менее двух водных квадратов. Общая площадь озер s = m1 × n1 + m2 × n2 + … + mk × nk не должна превосходить 106.
  Вывод. В единственной строке должны выводиться через пробел k значений, определяющих минимальные длины дамб.
В результате каждое озеро должно быть разделено на две части так, что водные клетки из разных частей не могут иметь общей стороны, не принадлежащей дамбе.
Тем не менее, касание этих клеток углами допускается. Каждая часть должна быть связана с берегом так, как это определялось выше.


ФИО: Ильин Константин Сергеевич
Группа: ПС-22
Среда разработки: Visual Studio 22
*/

#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

const std::string INPUT_FILE = "input.txt";
const std::string OUTPUT_FILE = "output.txt";

// Проверка, является ли клетка водой (с учётом границ матрицы)
bool IsWater(const std::vector<std::string>& grid, int row, int col)
{
	return row >= 0 && row < (int)grid.size() && col >= 0 && col < (int)grid[0].size() && grid[row][col] == '#';
}

// Проверка, относится ли клетка к "внешней суше" (берегу)
bool IsExternal(const std::vector<std::vector<bool>>& ext,
	int row, int col, int totalRows, int totalCols)
{
	if (row < 0 || row >= totalRows || col < 0 || col >= totalCols)
		return true;
	return ext[row][col];
}

// Чтение одного озера и добавление рамки из суши
std::vector<std::string> ReadLake(std::ifstream& fin, int& mi, int& ni)
{
	fin >> mi >> ni;
	int totalRows = mi + 2;
	int totalCols = ni + 2;
	std::vector<std::string> A(totalRows, std::string(totalCols, '.'));
	for (int i = 1; i <= mi; ++i)
	{
		std::string line;
		fin >> line;
		for (int j = 1; j <= ni; ++j)
		{
			A[i][j] = line[j - 1];
		}
	}
	return A;
}

// Поиск внешней суши (клетки '.', связанные с границей карты)
std::vector<std::vector<bool>> GetExternalLand(const std::vector<std::string>& grid)
{
	int totalRows = grid.size();
	int totalCols = grid[0].size(); // Было C, стало totalCols
	std::vector<std::vector<bool>> ext(totalRows, std::vector<bool>(totalCols, false));
	std::queue<std::pair<int, int>> q;
	q.push({ 0, 0 });
	ext[0][0] = true;
	int dirs[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
	while (!q.empty())
	{
		auto [r, c] = q.front();
		q.pop();
		for (auto [dr, dc] : dirs)
		{
			int nr = r + dr, nc = c + dc;
			if (nr >= 0 && nr < totalRows && nc >= 0 && nc < totalCols && !ext[nr][nc] && grid[nr][nc] == '.')
			{
				ext[nr][nc] = true;
				q.push({ nr, nc });
			}
		}
	}
	return ext;
}

// Является ли узел (i,j) сетки стартовым (инцидентен и воде, и берегу)
bool IsStartNode(const std::vector<std::string>& grid,
	const std::vector<std::vector<bool>>& ext,
	int i, int j, int totalRows, int totalCols)
{
	// Верхнее ребро
	if (i > 0)
	{
		int r1 = i - 1, c1 = j - 1, r2 = i - 1, c2 = j;
		bool w1 = IsWater(grid, r1, c1), w2 = IsWater(grid, r2, c2);
		if ((w1 && IsExternal(ext, r2, c2, totalRows, totalCols)) || (IsExternal(ext, r1, c1, totalRows, totalCols) && w2))
			return true;
	}
	// Нижнее ребро
	if (i < totalRows)
	{
		int r1 = i, c1 = j - 1, r2 = i, c2 = j;
		bool w1 = IsWater(grid, r1, c1), w2 = IsWater(grid, r2, c2);
		if ((w1 && IsExternal(ext, r2, c2, totalRows, totalCols)) || (IsExternal(ext, r1, c1, totalRows, totalCols) && w2))
			return true;
	}
	// Левое ребро
	if (j > 0)
	{
		int r1 = i - 1, c1 = j - 1, r2 = i, c2 = j - 1;
		bool w1 = IsWater(grid, r1, c1), w2 = IsWater(grid, r2, c2);
		if ((w1 && IsExternal(ext, r2, c2, totalRows, totalCols)) || (IsExternal(ext, r1, c1, totalRows, totalCols) && w2))
			return true;
	}
	// Правое ребро
	if (j < totalCols)
	{
		int r1 = i - 1, c1 = j, r2 = i, c2 = j;
		bool w1 = IsWater(grid, r1, c1), w2 = IsWater(grid, r2, c2);
		if ((w1 && IsExternal(ext, r2, c2, totalRows, totalCols)) || (IsExternal(ext, r1, c1, totalRows, totalCols) && w2))
			return true;
	}
	return false;
}

// Решение для одного озера: возвращает минимальную длину дамбы
int SolveLake(std::ifstream& fin)
{
	int mi, ni;
	std::vector<std::string> grid = ReadLake(fin, mi, ni);
	int totalRows = grid.size(); // mi + 2
	int totalCols = grid[0].size(); // ni + 2
	auto ext = GetExternalLand(grid);

	int nodesPerRow = totalCols + 1; // количество узлов в строке
	int nodesPerCol = totalRows + 1; // количество узлов в столбце
	int totalNodes = nodesPerRow * nodesPerCol;

	std::vector<int> dist(totalNodes, -1);
	std::vector<int> source(totalNodes, -1);
	std::queue<int> q;

	// Расставляем стартовые узлы
	for (int i = 0; i <= totalRows; ++i)
	{
		for (int j = 0; j <= totalCols; ++j)
		{
			if (IsStartNode(grid, ext, i, j, totalRows, totalCols))
			{
				int idx = i * nodesPerRow + j;
				dist[idx] = 0;
				source[idx] = idx;
				q.push(idx);
			}
		}
	}

	int ans = -1;
	// Проверяем соседние стартовые узлы (дамба длиной 1)
	// Это можно сделать внутри BFS, но проще проверить при инициализации
	for (int i = 0; i <= totalRows && ans == -1; ++i)
	{
		for (int j = 0; j <= totalCols && ans == -1; ++j)
		{
			int idx = i * nodesPerRow + j;
			if (dist[idx] != 0)
				continue;
			// Проверяем верхнего соседа
			if (i > 0 && IsWater(grid, i - 1, j - 1) && IsWater(grid, i - 1, j))
			{
				int nidx = (i - 1) * nodesPerRow + j;
				if (dist[nidx] == 0 && source[nidx] != source[idx])
					ans = 1;
			}
			// Проверяем левого соседа
			if (j > 0 && IsWater(grid, i - 1, j - 1) && IsWater(grid, i, j - 1))
			{
				int nidx = i * nodesPerRow + (j - 1);
				if (dist[nidx] == 0 && source[nidx] != source[idx])
					ans = 1;
			}
		}
	}
	// BFS
	while (!q.empty() && ans == -1)
	{
		int idx = q.front();
		q.pop();
		int i = idx / nodesPerRow;
		int j = idx % nodesPerRow;
		int d = dist[idx];
		int src = source[idx];

		// Вспомогательная лямбда для обработки одного направления
		auto tryMove = [&](int r1, int c1, int r2, int c2, int ni, int nj) {
			if (IsWater(grid, r1, c1) && IsWater(grid, r2, c2))
			{
				int nidx = ni * nodesPerRow + nj;
				if (dist[nidx] == -1)
				{
					dist[nidx] = d + 1;
					source[nidx] = src;
					q.push(nidx);
				}
				else if (source[nidx] != src)
				{
					ans = d + dist[nidx] + 1;
				}
			}
		};

		// Верхнее ребро (переход к узлу (i-1, j))
		if (i > 0)
			tryMove(i - 1, j - 1, i - 1, j, i - 1, j);
		if (ans != -1)
			break;

		// Нижнее ребро (переход к узлу (i+1, j))
		if (i < totalRows)
			tryMove(i, j - 1, i, j, i + 1, j);
		if (ans != -1)
			break;

		// Левое ребро (переход к узлу (i, j-1))
		if (j > 0)
			tryMove(i - 1, j - 1, i, j - 1, i, j - 1);
		if (ans != -1)
			break;

		// Правое ребро (переход к узлу (i, j+1))
		if (j < totalCols)
			tryMove(i - 1, j, i, j, i, j + 1);
	}

	return (ans == -1) ? 0 : ans;
}

int main()
{
	std::ifstream fin(INPUT_FILE);
	std::ofstream fout(OUTPUT_FILE);

	int k;
	fin >> k;
	std::vector<int> answers;
	for (int i = 0; i < k; ++i)
	{
		answers.push_back(SolveLake(fin));
	}

	for (size_t i = 0; i < answers.size(); ++i)
	{
		if (i)
			fout << ' ';
		fout << answers[i];
	}
	fout << std::endl;

	return 0;
}
