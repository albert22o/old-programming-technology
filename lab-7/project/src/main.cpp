#include <iostream>
#include "UMemory.h"

using namespace std;

int main()
{
    TMemory<int> mem;
    cout << "Initial state: " << mem.ReadState() << ", value = " << mem.ReadNumber() << endl;

    mem.Store(10);
    cout << "After Store(10): " << mem.ReadState() << ", value = " << mem.ReadNumber() << endl;

    mem.Add(5);
    cout << "After Add(5): " << mem.ReadState() << ", value = " << mem.ReadNumber() << endl;

    mem.Clear();
    cout << "After Clear(): " << mem.ReadState() << ", value = " << mem.ReadNumber() << endl;

    return 0;
}
