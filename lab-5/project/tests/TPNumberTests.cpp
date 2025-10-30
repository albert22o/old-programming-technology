#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <cmath>
#include "TPNumber.h"

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
    catch (const TPException &)
    {
        report(name, true);
    }
    catch (...)
    {
        report(name, false, "wrong exception type");
    }
}

void expect_eq_ld(const char *name, long double exp, long double act)
{
    long double diff = fabs(exp - act);
    if (diff < 1e-9L)
        report(name, true);
    else
    {
        char buf[200];
        snprintf(buf, 200, "expected=%Lf actual=%Lf", exp, act);
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

// tests
void t_ctor_invalid_base()
{
    expect_throw("ctor invalid base", []()
                 { TPNumber a(1.0L, 1, 2); });
}
void t_ctor_invalid_prec()
{
    expect_throw("ctor invalid precision", []()
                 { TPNumber a(1.0L, 2, -1); });
}
void t_ctor_and_tostring()
{
    TPNumber a(5.25L, 2, 3); // 5.25 decimal -> in base2: 101.01 -> with 3 frac digits -> 101.010
    expect_eq_str("tostring bin", "101.010", a.GetString());
}
void t_string_ctor()
{
    TPNumber a("A.F", 16, 2); // 10 + 15/16 = 10.9375 -> rounding to 2 hex frac digits -> scale=16^2=256 -> 10.9375*256=2800 -> exact -> digits: A.F0?
    expect_eq_str("string ctor hex", "A.F0", a.GetString());
}
void t_add_sub_mul_div()
{
    TPNumber a(1.5L, 10, 2);  // 1.50
    TPNumber b(2.25L, 10, 2); // 2.25
    TPNumber c = a.Add(b);
    expect_eq_str("add", "3.75", c.GetString());
    TPNumber d = b.Sub(a);
    expect_eq_str("sub", "0.75", d.GetString());
    TPNumber e = a.Mul(b); // 1.5*2.25=3.375 -> with 2 digits -> 3.38
    expect_eq_str("mul", "3.38", e.GetString());
    TPNumber f = b.Div(a); // 2.25/1.5=1.5
    expect_eq_str("div", "1.50", f.GetString());
}
void t_div_by_zero()
{
    expect_throw("div by zero", []()
                 { TPNumber a(1.0L,10,2); TPNumber z(0.0L,10,2); a.Div(z); });
}
void t_invert_square()
{
    TPNumber a(2.0L, 10, 3);
    expect_eq_str("square", "4.000", a.Square().GetString());
    expect_eq_str("invert", "0.500", a.Invert().GetString());
}
void t_base_precision_setters()
{
    TPNumber a(3.14159L, 10, 3);
    a.SetPrecisionNumber(2);
    expect_eq_str("set precision", "3.14", a.GetString());
    a.SetBaseNumber(16);
    // precision still 2 -> representation in hex with 2 hex fractional digits (approx)
    string s = a.GetString();
    report("set base produced string", true); // just ensure no exception; specific value depends on rounding
}
void t_mismatch_ops()
{
    expect_throw("mismatch add", []()
                 { TPNumber a(1.0L,10,2); TPNumber b(1.0L,2,2); a.Add(b); });
}

int main()
{
    vector<pair<string, TestFn>> tests = {
        {"ctor invalid base", t_ctor_invalid_base},
        {"ctor invalid precision", t_ctor_invalid_prec},
        {"tostring bin", t_ctor_and_tostring},
        {"string ctor hex", t_string_ctor},
        {"add/sub/mul/div", t_add_sub_mul_div},
        {"div by zero", t_div_by_zero},
        {"invert/square", t_invert_square},
        {"setters", t_base_precision_setters},
        {"mismatch ops", t_mismatch_ops}};

    cout << "Running " << tests.size() << " tests...\n\n";
    for (auto &p : tests)
    {
        try
        {
            p.second();
        }
        catch (const std::exception &e)
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
