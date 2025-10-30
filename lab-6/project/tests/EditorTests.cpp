#include <iostream>
#include <string>
#include "UEditor.h"

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
        TEditor e;
        report("default isZero", e.isZero());

        // add digits to imaginary part (default "0+0i")
        e.clear();
        e.edit(5); // add digit 5 -> imag becomes "5"
        report("add digit 5", e.getString() == "0+5i", e.getString().c_str());

        e.clear();
        e.edit(1);
        e.edit(2);
        e.edit(3); // 0+123i
        report("add digits 1 2 3", e.getString() == "0+123i", e.getString().c_str());

        // add decimal point
        e.clear();
        e.edit(TEditor::CMD_ADD_POINT);
        report("add point to imag", e.getString() == "0+0.i" || e.getString() == "0+0.i", e.getString().c_str());

        // toggle sign of imaginary
        e.setString("3.5+2i");
        e.edit(TEditor::CMD_ADD_SIGN);
        report("toggle imag sign", e.getString() == "3.5-2i", e.getString().c_str());
        e.edit(TEditor::CMD_ADD_SIGN);
        report("toggle imag sign back", e.getString() == "3.5+2i", e.getString().c_str());

        // backspace from imag
        e.setString("10+45i");
        e.edit(TEditor::CMD_BACKSPACE); // remove '5'
        report("backspace imag last digit", e.getString() == "10+4i", e.getString().c_str());
        e.edit(TEditor::CMD_BACKSPACE); // remove '4' -> imag becomes 0
        report("backspace imag becomes 0", e.getString() == "10+0i", e.getString().c_str());

        // backspace into real
        e.setString("12+0i");
        e.edit(TEditor::CMD_BACKSPACE); // imag single 0 -> backspace affects real
        // result should be "1+0i" by our implementation
        report("backspace into real", e.getString() == "1+0i", e.getString().c_str());

        // setString validation
        bool threw = false;
        try
        {
            e.setString("badstring");
        }
        catch (const TEditorException &)
        {
            threw = true;
        }
        report("setString invalid throws", threw);
    }
    catch (const std::exception &ex)
    {
        cout << "Uncaught exception: " << ex.what() << "\n";
        return 2;
    }
    return 0;
}
