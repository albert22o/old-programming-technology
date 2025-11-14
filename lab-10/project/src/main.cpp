#include <iostream>
#include "utset.h"

int main()
{
    tset_wrap<int> A;
    A.Add(1);
    A.Add(2);
    A.Add(3);
    tset_wrap<int> B;
    B.Add(3);
    B.Add(4);

    auto U = A.Union(B);
    std::cout << "Union Count = " << U.Count() << std::endl;
    std::cout << "Elements:";
    for (size_t i = 1; i <= U.Count(); ++i)
        std::cout << " " << U.Element(i);
    std::cout << std::endl;

    auto I = A.Intersect(B);
    std::cout << "Intersect Count = " << I.Count() << std::endl;
    if (!I.Empty())
        std::cout << "First intersect element: " << I.Element(1) << std::endl;

    A.Remove(2);
    std::cout << "A after remove 2, Count = " << A.Count() << std::endl;
    return 0;
}
