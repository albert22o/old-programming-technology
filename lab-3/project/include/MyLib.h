#pragma once
#include <vector>
#include <stdexcept>

namespace mylib
{

    class MyLib
    {
    public:
        // 1) Формирует b из нечётных цифр a в обратном порядке.
        static long long buildBFromOddDigits(long long a);

        // 2) Находит номер разряда r (нумерация справа->налево, от 1),
        //    где находится максимальное значение среди чётных номеров разрядов,
        //    содержащих чётные цифры. Возвращает 0, если подходящих разрядов нет.
        static int maxEvenPositionWithEvenDigit(long long n);

        // 3) Циклический сдвиг разрядов числа n на k позиций вправо.
        static long long cyclicRightShift(long long n, int k);

        // 4) Сумма чётных значений компонентов массива, лежащих выше побочной диагонали.
        static long long sumEvenAboveSecondaryDiagonal(const std::vector<std::vector<int>> &A);
    };

} // namespace mylib
