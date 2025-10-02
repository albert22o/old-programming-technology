#include "MyLib.h"
#include <string>
#include <algorithm>
#include <limits>

namespace mylib
{

    // helper for abs on long long
    static long long llabsll(long long x) { return x < 0 ? -x : x; }

    // 1) buildBFromOddDigits
    long long MyLib::buildBFromOddDigits(long long a)
    {
        long long x = llabsll(a);
        long long b = 0;
        bool any = false;
        // iterate digits right-to-left; append odd digits -> desired reversed odd digits
        while (x > 0)
        {
            int d = static_cast<int>(x % 10);
            if ((d % 2) != 0)
            {
                b = b * 10 + d;
                any = true;
            }
            x /= 10;
        }
        return any ? b : 0;
    }

    // 2) maxEvenPositionWithEvenDigit (positions numbered right->left starting from 1)
    int MyLib::maxEvenPositionWithEvenDigit(long long n)
    {
        std::string s = std::to_string(llabsll(n));
        int len = static_cast<int>(s.size());
        int bestPos = 0;
        int bestDigit = std::numeric_limits<int>::min();
        // positions right->left: position 1 -> s[len-1], position 2 -> s[len-2], ...
        for (int pos = 1; pos <= len; ++pos)
        {
            int idx = len - pos; // index in string
            if (idx < 0)
                break;
            if (pos % 2 == 0)
            { // only even positions (2,4,6,...)
                int digit = s[idx] - '0';
                if (digit % 2 == 0)
                {
                    if (digit > bestDigit)
                    {
                        bestDigit = digit;
                        bestPos = pos;
                    }
                    // if equal, keep first (i.e. larger pos? requirement ambiguous; we keep first encountered from pos=1..len,
                    // but since we iterate pos increasing, the first with max digit will be the smallest pos; that's fine)
                }
            }
        }
        return bestPos; // 0 if none found
    }

    // 3) cyclicRightShift
    long long MyLib::cyclicRightShift(long long n, int k)
    {
        if (k <= 0)
            return n;
        bool negative = n < 0;
        std::string s = std::to_string(llabsll(n));
        int len = static_cast<int>(s.size());
        if (len == 0)
            return n;
        k = k % len;
        if (k == 0)
            return n;
        // Right shift: last k digits to front
        std::string res = s.substr(len - k) + s.substr(0, len - k);
        long long val = 0;
        try
        {
            val = std::stoll(res);
        }
        catch (...)
        {
            return n; // on overflow return original
        }
        return negative ? -val : val;
    }

    // 4) sumEvenAboveSecondaryDiagonal
    long long MyLib::sumEvenAboveSecondaryDiagonal(const std::vector<std::vector<int>> &A)
    {
        if (A.empty())
            return 0;
        int rows = static_cast<int>(A.size());
        int cols = static_cast<int>(A[0].size()); // base columns (use first row's size)
        long long sum = 0;
        for (int i = 0; i < rows; ++i)
        {
            int rowCols = static_cast<int>(A[i].size());
            for (int j = 0; j < rowCols; ++j)
            {
                // above secondary diagonal: j < cols - 1 - i
                if (j < (cols - 1 - i))
                {
                    if ((A[i][j] % 2) == 0)
                        sum += A[i][j];
                }
            }
        }
        return sum;
    }

} // namespace mylib
