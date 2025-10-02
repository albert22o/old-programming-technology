#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cstdio>
#include "../include/MyLib.h"

using namespace std;
using namespace mylib;

static int g_total = 0;
static int g_passed = 0;
static int g_failed = 0;
using TestFn = function<void()>;

void report_result(const char *name, bool ok, const char *msg = nullptr)
{
    ++g_total;
    if (ok)
    {
        ++g_passed;
        cout << "[PASS] " << name << "\n";
    }
    else
    {
        ++g_failed;
        cout << "[FAIL] " << name;
        if (msg)
            cout << " -- " << msg;
        cout << "\n";
    }
}

void expect_eq_ll(const char *name, long long expected, long long actual)
{
    if (expected == actual)
        report_result(name, true);
    else
    {
        char buf[200];
        snprintf(buf, sizeof(buf), "expected=%lld actual=%lld", (long long)expected, (long long)actual);
        report_result(name, false, buf);
    }
}

void expect_eq_int(const char *name, int expected, int actual)
{
    if (expected == actual)
        report_result(name, true);
    else
    {
        char buf[200];
        snprintf(buf, sizeof(buf), "expected=%d actual=%d", expected, actual);
        report_result(name, false, buf);
    }
}

/* =====================
   Тесты (критерий C2 — наборы для путей)
   ===================== */

// buildBFromOddDigits
void t_buildB_12345() { expect_eq_ll("buildBFromOddDigits 12345 -> 531", 531, MyLib::buildBFromOddDigits(12345)); }
void t_buildB_2468() { expect_eq_ll("buildBFromOddDigits 2468 -> 0", 0, MyLib::buildBFromOddDigits(2468)); }
void t_buildB_neg() { expect_eq_ll("buildBFromOddDigits -135 -> 531", 531, MyLib::buildBFromOddDigits(-135)); }
void t_buildB_zero() { expect_eq_ll("buildBFromOddDigits 0 -> 0", 0, MyLib::buildBFromOddDigits(0)); }

// maxEvenPositionWithEvenDigit (right->left indexing)
void t_maxEvenPos_62543()
{
    // n=62543: digits right->left: pos1=3, pos2=4, pos3=5, pos4=2, pos5=6
    // even positions: pos2=4, pos4=2 -> max digit = 4 at pos2
    expect_eq_int("maxEvenPositionWithEvenDigit 62543 -> 2", 2, MyLib::maxEvenPositionWithEvenDigit(62543));
}
void t_maxEvenPos_noEven() { expect_eq_int("maxEvenPositionWithEvenDigit 13579 -> 0", 0, MyLib::maxEvenPositionWithEvenDigit(13579)); }
// tie/multi: n=28462 digits L->R: 2 8 4 6 2; R->L pos1=2,pos2=6,pos3=4,pos4=8,pos5=2
// even positions: pos2=6, pos4=8 -> max digit 8 at pos4 (right->left)
void t_maxEvenPos_tie() { expect_eq_int("maxEvenPositionWithEvenDigit 28462 -> 4", 4, MyLib::maxEvenPositionWithEvenDigit(28462)); }

// cyclicRightShift
void t_cyclic_123456_k2() { expect_eq_ll("cyclicRightShift 123456 k=2 -> 561234", 561234, MyLib::cyclicRightShift(123456, 2)); }
void t_cyclic_k0() { expect_eq_ll("cyclicRightShift 123 k=0 -> 123", 123, MyLib::cyclicRightShift(123, 0)); }
void t_cyclic_len_k() { expect_eq_ll("cyclicRightShift 123 k=3 -> 123", 123, MyLib::cyclicRightShift(123, 3)); }
void t_cyclic_neg() { expect_eq_ll("cyclicRightShift -12345 k=2 -> -45123", -45123, MyLib::cyclicRightShift(-12345, 2)); }

// sumEvenAboveSecondaryDiagonal
void t_sumEvenAbove_square()
{
    vector<vector<int>> A = {
        {2, 3, 4},
        {5, 6, 7},
        {8, 9, 10}};
    // cols=3; above secondary diagonal j < cols-1-i
    // i=0: j<2 -> j=0,1 : 2,3 -> even sum 2
    // i=1: j<1 -> j=0 : 5 -> odd
    // total = 2
    expect_eq_ll("sumEvenAboveSecondaryDiagonal square", 2, MyLib::sumEvenAboveSecondaryDiagonal(A));
}

void t_sumEvenAbove_rect()
{
    vector<vector<int>> A = {
        {2, 4, 6, 8},
        {1, 2, 3, 4},
        {5, 6, 7, 8}};
    // cols=4:
    // i=0: j<3 -> 2,4,6 -> evens sum 12
    // i=1: j<2 -> 1,2 -> even 2
    // i=2: j<1 -> 5 -> none
    // total = 14
    expect_eq_ll("sumEvenAboveSecondaryDiagonal rect", 14, MyLib::sumEvenAboveSecondaryDiagonal(A));
}

void t_sumEvenAbove_empty()
{
    vector<vector<int>> A;
    expect_eq_ll("sumEvenAboveSecondaryDiagonal empty -> 0", 0, MyLib::sumEvenAboveSecondaryDiagonal(A));
}

/* ================
   Список и запуск тестов
   ================ */

int main()
{
    vector<pair<string, TestFn>> tests = {
        {"buildB 12345", t_buildB_12345},
        {"buildB 2468", t_buildB_2468},
        {"buildB -135", t_buildB_neg},
        {"buildB 0", t_buildB_zero},

        {"maxEvenPos 62543", t_maxEvenPos_62543},
        {"maxEvenPos none", t_maxEvenPos_noEven},
        {"maxEvenPos tie", t_maxEvenPos_tie},

        {"cyclic 123456 k2", t_cyclic_123456_k2},
        {"cyclic k0", t_cyclic_k0},
        {"cyclic k==len", t_cyclic_len_k},
        {"cyclic negative", t_cyclic_neg},

        {"sumEvenAbove square", t_sumEvenAbove_square},
        {"sumEvenAbove rect", t_sumEvenAbove_rect},
        {"sumEvenAbove empty", t_sumEvenAbove_empty}};

    cout << "Running " << tests.size() << " tests...\n\n";
    for (const auto &p : tests)
    {
        try
        {
            p.second();
        }
        catch (const std::exception &e)
        {
            report_result(p.first.c_str(), false, e.what());
        }
        catch (...)
        {
            report_result(p.first.c_str(), false, "unknown exception");
        }
    }

    cout << "\n=================== Test summary ===================\n";
    cout << "Total:  " << g_total << "\n";
    cout << "Passed: " << g_passed << "\n";
    cout << "Failed: " << g_failed << "\n";
    cout << "====================================================\n";

    return (g_failed == 0) ? 0 : 1;
}
