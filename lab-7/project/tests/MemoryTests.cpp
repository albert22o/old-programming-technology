#include <iostream>
#include "UMemory.h"

using namespace std;

static void report(const char *name, bool ok, const char *msg = nullptr)
{
    cout << (ok ? "[PASS] " : "[FAIL] ") << name;
    if (msg)
        cout << " -- " << msg;
    cout << "\n";
}

int main()
{
    try
    {
        TMemory<int> mem;

        report("default state _Off", mem.ReadState() == "_Off");
        report("default value 0", mem.ReadNumber() == 0);

        mem.Store(5);
        report("store 5", mem.ReadNumber() == 5);
        report("state _On after store", mem.ReadState() == "_On");

        mem.Add(10);
        report("add 10", mem.ReadNumber() == 15);
        report("state _On after add", mem.ReadState() == "_On");

        mem.Clear();
        report("clear sets to 0", mem.ReadNumber() == 0);
        report("state _Off after clear", mem.ReadState() == "_Off");

        // Проверка обобщённости
        TMemory<double> m2;
        m2.Store(1.5);
        m2.Add(2.5);
        report("double add", m2.ReadNumber() == 4.0);
    }
    catch (const std::exception &ex)
    {
        cout << "Exception: " << ex.what() << "\n";
        return 1;
    }
    return 0;
}
