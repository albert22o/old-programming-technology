#pragma once
#include <vector>
#include <stdexcept>

namespace mylib
{

    class MyLib
    {
    public:
        static int min3(int x, int y, int z);

        // сумма элементов, у которых (i + j) чётная
        static double sumEvenIndexSum(const std::vector<std::vector<double>> &A);

        // максимум элементов на и ниже главной диагонали (i >= j)
        // бросает std::invalid_argument при отсутствии таких элементов
        static double maxOnAndBelowMainDiagonal(const std::vector<std::vector<double>> &A);
    };

} // namespace mylib
