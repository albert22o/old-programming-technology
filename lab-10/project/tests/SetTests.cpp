#include <iostream>
#include <cassert>
#include "utset.h"

static void report(const char *name, bool ok)
{
    std::cout << (ok ? "[PASS] " : "[FAIL] ") << name << std::endl;
}

int main()
{
    // test wrap variant with int
    tset_wrap<int> a;
    report("empty initially", a.Empty());
    a.Add(0);
    report("add element", a.Count() == 1 && a.Contains(0));
    a.Add(0);
    report("no duplicates", a.Count() == 1);
    a.Add(1);
    a.Add(2);
    report("count 3", a.Count() == 3);

    // Element
    try
    {
        int e1 = a.Element(1);
        report("element(1) ok", e1 == 0 || e1 == 1 || e1 == 2);
    }
    catch (...)
    {
        report("element(1) ok", false);
    }

    // Remove
    a.Remove(1);
    report("removed element", !a.Contains(1) && a.Count() == 2);

    // Union / Intersect / Difference
    tset_wrap<int> b;
    b.Add(2);
    b.Add(3);
    auto u = a.Union(b); // should contain 0,2,3 or similar
    report("union contains 3 elements", u.Count() == 3);
    auto inter = a.Intersect(b);
    report("intersect contains 1 (2)", inter.Count() == 1 && inter.Contains(2));
    auto diff = a.Difference(b);
    report("difference contains element 0 only", diff.Count() == 1 && diff.Contains(0));

    // inherit variant basic
    tset_inherit<int> hi;
    hi.Add(5);
    hi.Add(6);
    report("inherit add/count", hi.Count() == 2);

    std::cout << "All tests finished." << std::endl;
    return 0;
}
