#include <iostream>
#include <cmath>
#include "UPoly.h"

static void report(const char *name, bool ok)
{
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << std::endl;
}

int main()
{
    // default zero polynomial
    TPoly p0;
    report("p0 is zero", p0.Count() == 0 && p0.Degree() == 0);

    // constructor single term
    TPoly p1(1, 0); // 1
    report("p1 degree 0", p1.Degree() == 0);
    report("p1 coeff 0 == 1", p1.Coeff(0) == 1);

    // addition
    TPoly a(1, 0);
    TPoly b(1, 1);
    TPoly c = a + b; // 1 + x
    report("1 + x degree == 1", c.Degree() == 1);
    report("coeff x == 1", c.Coeff(1) == 1);
    report("coeff 0 == 1", c.Coeff(0) == 1);

    // multiplication
    TPoly d = c * c; // 1 + 2x + x^2
    report("c*c degree 2", d.Degree() == 2);
    report("coeff x == 2", d.Coeff(1) == 2);
    report("coeff x^2 == 1", d.Coeff(2) == 1);

    // subtraction
    TPoly f = d - TPoly(1, 0); // remove 1 -> 2x + x^2
    report("d-1 coeff 0 == 0", f.Coeff(0) == 0);

    // derivative
    TPoly diff = d.Diff(); // derivative 2 + 2x
    report("diff degree 1", diff.Degree() == 1);
    report("diff coeff 1 == 2", diff.Coeff(1) == 2);
    report("diff coeff 0 == 2", diff.Coeff(0) == 2);

    // eval
    double val = d.Eval(2.0); // 1 + 4 + 4 = 9
    report("d(2) == 9", std::abs(val - 9.0) < 1e-9);

    // equality
    TPoly copy = d;
    report("copy equals original", copy == d);

    // zero handling
    TPoly zero;
    TPoly mulZero = d * zero;
    report("mul by zero is zero", mulZero.Count() == 0);

    std::cout << "All tests finished." << std::endl;
    return 0;
}
