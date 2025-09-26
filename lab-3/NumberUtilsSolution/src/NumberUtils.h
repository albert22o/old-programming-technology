#pragma once
#include <vector>
#include <string>

namespace nu
{

    class NumberUtils
    {
    public:
        // 1) Формирует целое число из нечётных цифр a в обратном порядке.
        //    Работает с абсолютным значением a; возвращает неотрицательное b.
        static long long OddDigitsReversed(long long a);

        // 2) Находит номер разряда r (справа->слева, нумерация от 1),
        //    в котором находится максимальное значение среди чётных номеров разрядов,
        //    содержащих чётные цифры. Если подходящих разрядов нет, возвращает 0.
        static int MaxDigitPositionAmongEvenPositions(long long n);

        // 3) Циклический сдвиг цифр числа n вправо на k позиций.
        //    Сохраняет знак числа.
        static long long CyclicRightShift(long long n, int k);

        // 4) Сумма чётных значений элементов массива A, лежащих выше побочной диагонали.
        //    A — вектор строк, каждая строка имеет одинаковую длину.
        static long long SumEvenAboveSecondaryDiagonal(const std::vector<std::vector<int>> &A);
    };

} // namespace nu
