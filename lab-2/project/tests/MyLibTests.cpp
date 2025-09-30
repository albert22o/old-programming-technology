#include <iostream>
#include <vector>
#include <cmath>
#include <exception>
#include <functional>
#include <string>
#include <cstdio>             // snprintf
#include "../include/MyLib.h" // путь относительно tests_simple; поправьте, если структура другая

using namespace std;
using namespace mylib;

// глобальная статистика
static int g_total = 0;
static int g_passed = 0;
static int g_failed = 0;

// Регистрация тестов: каждый тест — пара (имя, функция)
using TestFn = std::function<void()>;

// Утилиты для отчёта
void report_result(const char *test_name, bool ok, const char *msg = nullptr)
{
    ++g_total;
    if (ok)
    {
        ++g_passed;
        cout << "[PASS] " << test_name << "\n";
    }
    else
    {
        ++g_failed;
        cout << "[FAIL] " << test_name;
        if (msg)
            cout << " -- " << msg;
        cout << "\n";
    }
}

void expect_eq_int(const char *name, long long expected, long long actual)
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

void expect_eq_double(const char *name, double expected, double actual, double tol = 1e-9)
{
    if (std::fabs(expected - actual) <= tol)
        report_result(name, true);
    else
    {
        char buf[200];
        snprintf(buf, sizeof(buf), "expected=%.12g actual=%.12g", expected, actual);
        report_result(name, false, buf);
    }
}

// Шаблонная версия: принимает любой callable (включая лямбды)
template <typename F>
void expect_throw_invalidarg(const char *name, F &&f)
{
    try
    {
        f();
        report_result(name, false, "expected std::invalid_argument but no exception thrown");
    }
    catch (const std::invalid_argument &e)
    {
        report_result(name, true);
    }
    catch (const std::exception &e)
    {
        report_result(name, false, "different std::exception thrown");
    }
    catch (...)
    {
        report_result(name, false, "non-standard exception thrown");
    }
}

/* -------------------
   Тесты (C1)
   ------------------- */

// Каждый тест — просто функция, которую мы потом регистрируем
void test_min3_3_2_1()
{
    expect_eq_int("min3(3,2,1) == 1", 1, MyLib::min3(3, 2, 1));
}

void test_min3_1_2_3()
{
    expect_eq_int("min3(1,2,3) == 1", 1, MyLib::min3(1, 2, 3));
}

void test_min3_withEquals()
{
    expect_eq_int("min3(5,5,2) == 2", 2, MyLib::min3(5, 5, 2));
}

void test_min3_negative()
{
    expect_eq_int("min3(-1,-5,0) == -5", -5, MyLib::min3(-1, -5, 0));
}

// sumEvenIndexSum tests
void test_sumEvenIndexSum_2x2()
{
    vector<vector<double>> A = {{1, 2}, {3, 4}};
    expect_eq_double("sumEvenIndexSum 2x2", 5.0, MyLib::sumEvenIndexSum(A));
}

void test_sumEvenIndexSum_1x3()
{
    vector<vector<double>> A = {{1, 2, 3}};
    expect_eq_double("sumEvenIndexSum 1x3", 4.0, MyLib::sumEvenIndexSum(A));
}

void test_sumEvenIndexSum_empty()
{
    vector<vector<double>> A;
    expect_eq_double("sumEvenIndexSum empty", 0.0, MyLib::sumEvenIndexSum(A));
}

// maxOnAndBelowMainDiagonal tests
void test_maxOnAndBelow_square3x3()
{
    vector<vector<double>> A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};
    expect_eq_double("maxOnAndBelow 3x3", 9.0, MyLib::maxOnAndBelowMainDiagonal(A));
}

void test_maxOnAndBelow_rectangular2x3()
{
    vector<vector<double>> A = {
        {-1, 5, 6},
        {7, 2, 3}};
    expect_eq_double("maxOnAndBelow 2x3", 7.0, MyLib::maxOnAndBelowMainDiagonal(A));
}

void test_maxOnAndBelow_single()
{
    vector<vector<double>> A = {{42}};
    expect_eq_double("maxOnAndBelow single", 42.0, MyLib::maxOnAndBelowMainDiagonal(A));
}

void test_maxOnAndBelow_empty_throws()
{
    vector<vector<double>> A;
    expect_throw_invalidarg("maxOnAndBelow empty throws", [&]()
                            { MyLib::maxOnAndBelowMainDiagonal(A); });
}

/* -------------------
   Регистрация и запуск
   ------------------- */

int main()
{
    // Регистрируем тесты в массиве (порядок выполнения можно изменить)
    vector<pair<string, TestFn>> tests = {
        // min3
        {"min3(3,2,1) == 1", test_min3_3_2_1},
        {"min3(1,2,3) == 1", test_min3_1_2_3},
        {"min3(5,5,2) == 2", test_min3_withEquals},
        {"min3(-1,-5,0) == -5", test_min3_negative},

        // sumEvenIndexSum
        {"sumEvenIndexSum 2x2", test_sumEvenIndexSum_2x2},
        {"sumEvenIndexSum 1x3", test_sumEvenIndexSum_1x3},
        {"sumEvenIndexSum empty", test_sumEvenIndexSum_empty},

        // maxOnAndBelowMainDiagonal
        {"maxOnAndBelow 3x3", test_maxOnAndBelow_square3x3},
        {"maxOnAndBelow 2x3", test_maxOnAndBelow_rectangular2x3},
        {"maxOnAndBelow single", test_maxOnAndBelow_single},
        {"maxOnAndBelow empty throws", test_maxOnAndBelow_empty_throws}};

    cout << "Running " << tests.size() << " tests...\n\n";

    for (const auto &p : tests)
    {
        const string &name = p.first;
        try
        {
            p.second(); // выполнить тест
        }
        catch (const std::exception &e)
        {
            // если во время теста неожиданно выброшено исключение
            report_result(name.c_str(), false, e.what());
        }
        catch (...)
        {
            report_result(name.c_str(), false, "unknown exception during test");
        }
    }

    cout << "\n=================== Test summary ===================\n";
    cout << "Total:  " << g_total << "\n";
    cout << "Passed: " << g_passed << "\n";
    cout << "Failed: " << g_failed << "\n";
    cout << "====================================================\n";

    // Возврат кода: 0 если все тесты прошли, иначе 1
    return (g_failed == 0) ? 0 : 1;
}
