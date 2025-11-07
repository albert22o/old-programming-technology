#include <iostream>
#include "UProc.h"
using namespace std;

int main()
{
    TProc<double> cpu;

    cpu.Lop_Res_Set(5);
    cpu.Rop_Set(3);
    cpu.OprtnSet(Add);
    cpu.OprtnRun();
    cout << "Add: " << cpu.ReadLop() << endl;

    cpu.Rop_Set(2);
    cpu.OprtnSet(Mul);
    cpu.OprtnRun();
    cout << "Mul: " << cpu.ReadLop() << endl;

    cpu.Rop_Set(4);
    cpu.FuncRun(Sqr);
    cout << "Sqr: " << cpu.ReadRop() << endl;

    cpu.Rop_Set(2);
    cpu.FuncRun(Rev);
    cout << "Rev: " << cpu.ReadRop() << endl;

    cpu.ReSet();
    cout << "After reset: " << cpu.ReadLop() << ", " << cpu.ReadRop() << endl;
}
