#include <iostream>
#include "UProc.h"
using namespace std;

static void report(const char *name, bool ok)
{
    cout << (ok ? "[PASS] " : "[FAIL] ") << name << "\n";
}

int main()
{
    TProc<double> cpu;

    report("default state None", cpu.ReadState() == None);
    report("default Lop_Res 0", cpu.ReadLop() == 0);
    report("default Rop 0", cpu.ReadRop() == 0);

    cpu.Lop_Res_Set(5);
    cpu.Rop_Set(3);
    cpu.OprtnSet(Add);
    cpu.OprtnRun();
    report("Add 5+3=8", cpu.ReadLop() == 8);

    cpu.Rop_Set(2);
    cpu.OprtnSet(Mul);
    cpu.OprtnRun();
    report("Mul 8*2=16", cpu.ReadLop() == 16);

    cpu.Rop_Set(4);
    cpu.FuncRun(Sqr);
    report("Sqr 4^2=16", cpu.ReadRop() == 16);

    cpu.Rop_Set(2);
    cpu.FuncRun(Rev);
    report("Rev 1/2=0.5", cpu.ReadRop() == 0.5);

    cpu.ReSet();
    report("After reset Lop=0", cpu.ReadLop() == 0);
    report("After reset Rop=0", cpu.ReadRop() == 0);
    report("After reset state=None", cpu.ReadState() == None);
}
