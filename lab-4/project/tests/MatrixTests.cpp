// tests/MatrixTests.cpp
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include "../include/Matrix.h"

using namespace std;

static int g_total = 0, g_passed = 0, g_failed = 0;
using TestFn = function<void()>;

void report(const char *name, bool ok, const char *msg = nullptr)
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

void expect_throw(const char *name, function<void()> f)
{
    try
    {
        f();
        report(name, false, "expected exception");
    }
    catch (const MyException &)
    {
        report(name, true);
    }
    catch (...)
    {
        report(name, false, "wrong exception type");
    }
}

void expect_eq_int(const char *name, int exp, int act)
{
    if (exp == act)
        report(name, true);
    else
    {
        char buf[200];
        snprintf(buf, 200, "expected=%d actual=%d", exp, act);
        report(name, false, buf);
    }
}

void expect_eq_str(const char *name, const string &exp, const string &act)
{
    if (exp == act)
        report(name, true);
    else
    {
        string msg = "expected=\"" + exp + "\" actual=\"" + act + "\"";
        report(name, false, msg.c_str());
    }
}

/* ---- Tests (C2): constructor, indexer, add, sub, mul, eq, transp, min, tostring ---- */

void t_ctor_invalid_rows()
{
    expect_throw("ctor invalid rows", []()
                 { Matrix a(0, 2); });
}
void t_ctor_invalid_cols()
{
    expect_throw("ctor invalid cols", []()
                 { Matrix a(2, 0); });
}
void t_ctor_ok()
{
    Matrix a(2, 3);
    report("ctor ok", true);
}

void t_index_set_get_ok()
{
    Matrix a(2, 2);
    a.set(0, 0, 5);
    a.set(1, 1, 7);
    expect_eq_int("index set/get (0,0)", 5, a.get(0, 0));
    expect_eq_int("index set/get (1,1)", 7, a.get(1, 1));
}
void t_index_set_invalid()
{
    expect_throw("index set invalid", []()
                 { Matrix a(2,2); a.set(2,0,1); });
}
void t_index_get_invalid()
{
    expect_throw("index get invalid", []()
                 { Matrix a(2,2); a.get(0,2); });
}

void t_add_ok()
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(1, 0, 3);
    a.set(1, 1, 4);
    b.set(0, 0, 10);
    b.set(0, 1, 20);
    b.set(1, 0, 30);
    b.set(1, 1, 40);
    Matrix c = a + b;
    expect_eq_int("add (0,0)", 11, c.get(0, 0));
    expect_eq_int("add (1,1)", 44, c.get(1, 1));
}
void t_add_dim_mismatch()
{
    expect_throw("add dim mismatch", []()
                 { Matrix a(2,2); Matrix b(3,2); Matrix c = a + b; });
}

void t_sub_ok()
{
    Matrix a(2, 1);
    Matrix b(2, 1);
    a.set(0, 0, 5);
    a.set(1, 0, 8);
    b.set(0, 0, 2);
    b.set(1, 0, 3);
    Matrix c = a - b;
    expect_eq_int("sub (1,0)", 5, c.get(1, 0));
}
void t_mul_ok()
{
    Matrix a(2, 3);
    Matrix b(3, 2);
    // a = [[1,2,3],[4,5,6]]
    int val = 1;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 3; j++)
            a.set(i, j, val++);
    // b = [[1,2],[3,4],[5,6]]
    val = 1;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            b.set(i, j, val++);
    Matrix c = a * b; // result 2x2: [[22,28],[49,64]]
    expect_eq_int("mul (0,0)", 22, c.get(0, 0));
    expect_eq_int("mul (1,1)", 64, c.get(1, 1));
}
void t_mul_dim_mismatch()
{
    expect_throw("mul dim mismatch", []()
                 { Matrix a(2,2); Matrix b(3,3); Matrix c = a * b; });
}

void t_eq_true()
{
    Matrix a(2, 2);
    Matrix b(2, 2);
    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(1, 0, 3);
    a.set(1, 1, 4);
    b.set(0, 0, 1);
    b.set(0, 1, 2);
    b.set(1, 0, 3);
    b.set(1, 1, 4);
    bool r = (a == b);
    if (r)
        report("eq true", true);
    else
        report("eq true", false, "expected true");
}
void t_eq_dim_mismatch()
{
    expect_throw("eq dim mismatch", []()
                 { Matrix a(2,2); Matrix b(2,3); bool r = (a == b); (void)r; });
}

void t_transp_ok()
{
    Matrix a(2, 2);
    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(1, 0, 3);
    a.set(1, 1, 4);
    Matrix t = a.Transp();
    expect_eq_int("transp (0,1)", 3, t.get(0, 1));
}
void t_transp_not_square()
{
    expect_throw("transp not square", []()
                 { Matrix a(2,3); Matrix t = a.Transp(); (void)t; });
}

void t_min_ok()
{
    Matrix a(2, 2);
    a.set(0, 0, 5);
    a.set(0, 1, -1);
    a.set(1, 0, 3);
    a.set(1, 1, 0);
    expect_eq_int("min ok", -1, a.Min());
}

void t_to_string()
{
    Matrix a(2, 2);
    a.set(0, 0, 1);
    a.set(0, 1, 2);
    a.set(1, 0, 3);
    a.set(1, 1, 4);
    expect_eq_str("ToString", "{{1,2},{3,4}}", a.ToString());
}

int main()
{
    vector<pair<string, TestFn>> tests = {
        {"ctor invalid rows", t_ctor_invalid_rows},
        {"ctor invalid cols", t_ctor_invalid_cols},
        {"ctor ok", t_ctor_ok},

        {"index set/get ok", t_index_set_get_ok},
        {"index set invalid", t_index_set_invalid},
        {"index get invalid", t_index_get_invalid},

        {"add ok", t_add_ok},
        {"add dim mismatch", t_add_dim_mismatch},

        {"sub ok", t_sub_ok},

        {"mul ok", t_mul_ok},
        {"mul dim mismatch", t_mul_dim_mismatch},

        {"eq true", t_eq_true},
        {"eq dim mismatch", t_eq_dim_mismatch},

        {"transp ok", t_transp_ok},
        {"transp not square", t_transp_not_square},

        {"min ok", t_min_ok},
        {"ToString", t_to_string}};

    cout << "Running " << tests.size() << " tests...\n\n";
    for (auto &p : tests)
    {
        try
        {
            p.second();
        }
        catch (const exception &e)
        {
            report(p.first.c_str(), false, e.what());
        }
        catch (...)
        {
            report(p.first.c_str(), false, "unknown exception");
        }
    }

    cout << "\nSummary: total=" << g_total << " passed=" << g_passed << " failed=" << g_failed << "\n";
    return (g_failed == 0) ? 0 : 1;
}
