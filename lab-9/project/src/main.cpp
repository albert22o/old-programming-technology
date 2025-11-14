#include <iostream>
#include "UPoly.h"

int main()
{
    TPoly a(1, 0);   // 1
    TPoly b(1, 1);   // x
    TPoly c = a + b; // 1 + x
    std::cout << "c = " << c.ToString() << std::endl;

    TPoly d = c * c; // (1+x)^2 = 1 + 2x + x^2
    std::cout << "d = " << d.ToString() << std::endl;

    TPoly e = d.Diff(); // derivative
    std::cout << "d' = " << e.ToString() << std::endl;

    std::cout << "d(2) = " << d.Eval(2.0) << std::endl;
    return 0;
}
