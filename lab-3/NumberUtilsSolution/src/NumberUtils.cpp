#include "NumberUtils.h"
#include <algorithm>
#include <cmath>
#include <limits>

using namespace std;

namespace nu
{

    long long NumberUtils::OddDigitsReversed(long long a)
    {
        long long x = llabs(a);
        long long b = 0;
        bool found = false;
        while (x > 0)
        {
            int d = static_cast<int>(x % 10);
            if (d % 2 == 1)
            {                   // нечётная
                b = b * 10 + d; // *ВАЖНО*: мы идём справа->слева, добавляем цифру в конец результата
                found = true;
            }
            x /= 10;
        }
        // Если ни одной нечётной цифры — возвращаем 0.
        return b;
    }

    int NumberUtils::MaxDigitPositionAmongEvenPositions(long long n)
    {
        long long x = llabs(n);
        // нумерация справа->слева, начиная с 1
        int pos = 1;
        int bestPos = 0;
        int bestDigit = std::numeric_limits<int>::min();
        while (x > 0)
        {
            int d = static_cast<int>(x % 10);
            if ((pos % 2) == 0)
            { // чётная позиция
                if ((d % 2) == 0)
                { // цифра четная
                    if (d > bestDigit)
                    {
                        bestDigit = d;
                        bestPos = pos;
                    }
                }
            }
            x /= 10;
            pos++;
        }
        // если ничего не найдено — вернуть 0
        return bestPos;
    }

    long long NumberUtils::CyclicRightShift(long long n, int k)
    {
        if (k == 0)
            return n;
        bool negative = n < 0;
        string s = to_string(negative ? -n : n);
        int len = static_cast<int>(s.size());
        if (len == 0)
            return n;
        k = ((k % len) + len) % len; // нормализуем
        if (k == 0)
            return n;
        string res = s.substr(len - k) + s.substr(0, len - k);
        // избежать ведущих нулей проблем: интерпретация как long long
        long long val = 0;
        for (char c : res)
        {
            val = val * 10 + (c - '0');
        }
        return negative ? -val : val;
    }

    long long NumberUtils::SumEvenAboveSecondaryDiagonal(const vector<vector<int>> &A)
    {
        if (A.empty())
            return 0;
        size_t rows = A.size();
        size_t cols = A[0].size();
        // проверить, что все строки имеют одинаковый размер
        for (const auto &row : A)
        {
            if (row.size() != cols)
                return 0; // некорректный массив — возвращаем 0
        }
        long long sum = 0;
        // побочная диагональ: i + j == cols - 1
        for (size_t i = 0; i < rows; ++i)
        {
            for (size_t j = 0; j < cols; ++j)
            {
                if (static_cast<int>(i + j) < static_cast<int>(cols - 1))
                { // выше побочной диагонали
                    if ((A[i][j] % 2) == 0)
                        sum += A[i][j];
                }
            }
        }
        return sum;
    }

} // namespace nu
