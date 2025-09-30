#include "MyLib.h"
#include <limits>

namespace mylib
{

    int MyLib::min3(int x, int y, int z)
    {
        int m = x;
        if (m > y)
            m = y;
        if (m > z)
            m = z;
        return m;
    }

    double MyLib::sumEvenIndexSum(const std::vector<std::vector<double>> &A)
    {
        if (A.empty())
            return 0.0;
        double sum = 0.0;
        for (size_t i = 0; i < A.size(); ++i)
        {
            if (A[i].empty())
                continue;
            for (size_t j = 0; j < A[i].size(); ++j)
            {
                if (((i + j) % 2) == 0)
                {
                    sum += A[i][j];
                }
            }
        }
        return sum;
    }

    double MyLib::maxOnAndBelowMainDiagonal(const std::vector<std::vector<double>> &A)
    {
        if (A.empty())
            throw std::invalid_argument("Matrix is empty");
        bool found = false;
        double mx = -std::numeric_limits<double>::infinity();
        for (size_t i = 0; i < A.size(); ++i)
        {
            if (A[i].empty())
                continue;
            for (size_t j = 0; j < A[i].size(); ++j)
            {
                if (i >= j)
                {
                    if (!found)
                    {
                        mx = A[i][j];
                        found = true;
                    }
                    else if (A[i][j] > mx)
                        mx = A[i][j];
                }
            }
        }
        if (!found)
            throw std::invalid_argument("No elements on or below main diagonal");
        return mx;
    }

} // namespace mylib
