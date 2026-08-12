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
#include <iostream>

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

    int X, Y;
    if (!(fin >> X >> Y))
    {
        std::cout << "couldnt read file" << std::endl;
        return 1;
    }

    std::vector<std::vector<long long>> dp(Y + 1, std::vector<long long>(X + Y + 2, 0));

    dp[0][X] = 1;

    for (int step = 1; step <= Y; step++)
    {
        // Переходы для всех позиций, кроме 0 (цели)
        for (int pos = 1; pos <= X + Y; pos++)
        {
            // Шаг к цели (уменьшаем расстояние)
            if (pos - 1 >= 0)
            {
                dp[step][pos - 1] += dp[step - 1][pos];
            }
            // Шаг от цели (увеличиваем расстояние)
            if (pos + 1 <= X + Y)
            {
                dp[step][pos + 1] += dp[step - 1][pos];
            }
        }
    }

    fout << dp[Y][0] << std::endl;

    return 0;
}
