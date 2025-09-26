#include "NumberUtils.h"
#include <gtest/gtest.h>
#include <vector>

using namespace nu;
using namespace std;

// Тесты подготовлены по критерию C2 (покрытие путей / условий)
// 1) OddDigitsReversed
TEST(OddDigitsReversedTests, BasicExample)
{
    EXPECT_EQ(NumberUtils::OddDigitsReversed(12345), 531);
}
TEST(OddDigitsReversedTests, NoOddDigits)
{
    EXPECT_EQ(NumberUtils::OddDigitsReversed(2468), 0);
}
TEST(OddDigitsReversedTests, SingleDigitOdd)
{
    EXPECT_EQ(NumberUtils::OddDigitsReversed(7), 7);
}
TEST(OddDigitsReversedTests, NegativeInput)
{
    EXPECT_EQ(NumberUtils::OddDigitsReversed(-13579), 97531);
}
TEST(OddDigitsReversedTests, TrailingZeros)
{
    EXPECT_EQ(NumberUtils::OddDigitsReversed(1010305), 5311); // digits right->left:5,0,3,0,1,0,1 -> odd:5,3,1,1 -> 5 3 1 1 -> 5311
}

// 2) MaxDigitPositionAmongEvenPositions
TEST(MaxDigitPositionTests, ExampleRightToLeft)
{
    // Право->Лево нумерация: 62543 -> pos1=3,pos2=4,pos3=5,pos4=2,pos5=6 => even positions: pos2(d=4),pos4(d=2) => max=4 at pos2
    EXPECT_EQ(NumberUtils::MaxDigitPositionAmongEvenPositions(62543), 2);
}
TEST(MaxDigitPositionTests, NoEvenPositionsWithEvenDigits)
{
    EXPECT_EQ(NumberUtils::MaxDigitPositionAmongEvenPositions(13579), 0); // нет чётных цифр на чётных позициях
}
TEST(MaxDigitPositionTests, MultipleEqualMax)
{
    // 482424 -> digits r->l:4,2,4,2,8,4 ; even positions: pos2=2,pos4=2,pos6=4 => max=4 at pos6
    EXPECT_EQ(NumberUtils::MaxDigitPositionAmongEvenPositions(482424), 6);
}
TEST(MaxDigitPositionTests, SingleDigit)
{
    EXPECT_EQ(NumberUtils::MaxDigitPositionAmongEvenPositions(8), 0); // нет чётной позиции
}

// 3) CyclicRightShift
TEST(CyclicShiftTests, BasicShift)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(123456, 2), 561234);
}
TEST(CyclicShiftTests, ShiftByZero)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(123, 0), 123);
}
TEST(CyclicShiftTests, ShiftByLength)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(12345, 5), 12345);
}
TEST(CyclicShiftTests, ShiftGreaterThanLength)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(12345, 7), NumberUtils::CyclicRightShift(12345, 7 % 5));
}
TEST(CyclicShiftTests, NegativeNumber)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(-12345, 2), -45123);
}
TEST(CyclicShiftTests, LeadingZerosAfterShift)
{
    EXPECT_EQ(NumberUtils::CyclicRightShift(1002, 1), 2100); // '1002' -> right shift 1 -> '2100'
}

// 4) SumEvenAboveSecondaryDiagonal
TEST(SumEvenAboveSecondaryTests, SquareMatrix)
{
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    // cols=3 -> secondary diagonal: i+j==2
    // positions above (i+j < 2): (0,0),(0,1),(1,0) -> values 1,2,4 -> only even: 2,4 => sum=6
    EXPECT_EQ(NumberUtils::SumEvenAboveSecondaryDiagonal(A), 6);
}
TEST(SumEvenAboveSecondaryTests, RectangularMatrix)
{
    vector<vector<int>> A = {
        {2, 4, 6, 8},
        {1, 3, 5, 7}};
    // cols=4 -> i+j<3 -> pairs: (0,0),(0,1),(0,2),(1,0),(1,1) etc. Filter even values -> sum accordingly
    EXPECT_EQ(NumberUtils::SumEvenAboveSecondaryDiagonal(A), 2 + 4 + 6 + 0 + 0); // =12
}
TEST(SumEvenAboveSecondaryTests, EmptyMatrix)
{
    vector<vector<int>> A;
    EXPECT_EQ(NumberUtils::SumEvenAboveSecondaryDiagonal(A), 0);
}
TEST(SumEvenAboveSecondaryTests, NonRectangularMatrix)
{
    vector<vector<int>> A = {
        {1, 2, 3},
        {4, 5} // non-rectangular -> function returns 0 per implementation
    };
    EXPECT_EQ(NumberUtils::SumEvenAboveSecondaryDiagonal(A), 0);
}
