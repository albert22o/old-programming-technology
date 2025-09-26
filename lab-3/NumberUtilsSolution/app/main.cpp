#include <iostream>
#include "NumberUtils.h"
#include <vector>

using namespace std;
using namespace nu;

int main()
{
    cout << "Demo NumberUtils\n";

    long long a = 12345;
    cout << "OddDigitsReversed(" << a << ") = " << NumberUtils::OddDigitsReversed(a) << "\n";

    long long n = 62543;
    cout << "MaxDigitPositionAmongEvenPositions(" << n << ") = " << NumberUtils::MaxDigitPositionAmongEvenPositions(n) << " (positions counted right->left)\n";

    long long m = 123456;
    cout << "CyclicRightShift(" << m << ", 2) = " << NumberUtils::CyclicRightShift(m, 2) << "\n";

    vector<vector<int>> A = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}};
    cout << "SumEvenAboveSecondaryDiagonal = " << NumberUtils::SumEvenAboveSecondaryDiagonal(A) << "\n";

    return 0;
}
