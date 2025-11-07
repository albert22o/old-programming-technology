#pragma once
#include <stdexcept>

enum TOprtn
{
    None,
    Add,
    Sub,
    Mul,
    Dvd
};
enum TFunc
{
    Rev,
    Sqr
};

template <class T>
class TProc
{
private:
    T Lop_Res;
    T Rop;
    TOprtn Operation;

public:
    TProc() : Lop_Res(T()), Rop(T()), Operation(None) {}

    void ReSet()
    {
        Lop_Res = T();
        Rop = T();
        Operation = None;
    }

    void OprtnClear() { Operation = None; }

    void OprtnSet(TOprtn op) { Operation = op; }

    void Lop_Res_Set(const T &val) { Lop_Res = val; }

    void Rop_Set(const T &val) { Rop = val; }

    TOprtn ReadState() const { return Operation; }

    T ReadLop() const { return Lop_Res; }

    T ReadRop() const { return Rop; }

    void OprtnRun()
    {
        switch (Operation)
        {
        case Add:
            Lop_Res = Lop_Res + Rop;
            break;
        case Sub:
            Lop_Res = Lop_Res - Rop;
            break;
        case Mul:
            Lop_Res = Lop_Res * Rop;
            break;
        case Dvd:
            if (Rop == 0)
                throw std::runtime_error("Division by zero");
            Lop_Res = Lop_Res / Rop;
            break;
        default:
            break;
        }
    }

    void FuncRun(TFunc f)
    {
        switch (f)
        {
        case Rev:
            if (Rop == 0)
                throw std::runtime_error("Division by zero");
            Rop = T(1) / Rop;
            break;
        case Sqr:
            Rop = Rop * Rop;
            break;
        }
    }
};
