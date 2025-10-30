#pragma once
#include <string>
#include <stdexcept>

class TEditorException : public std::runtime_error
{
public:
    explicit TEditorException(const std::string &s) : std::runtime_error(s) {}
};

class TEditor
{
public:
    // commands for edit(int)
    // 0..9 -> add corresponding digit
    // 10 -> add sign (toggle sign of imaginary part)
    // 11 -> add decimal separator to current part
    // 12 -> backspace (delete right-most editable symbol)
    // 13 -> clear (set to zero)
    enum
    {
        CMD_ADD_SIGN = 10,
        CMD_ADD_POINT = 11,
        CMD_BACKSPACE = 12,
        CMD_CLEAR = 13
    };

    TEditor();                            // constructor
    bool isZero() const;                  // true if complex number is zero
    std::string addSign();                // toggle sign of imaginary part, return string
    std::string addDigit(int d);          // add digit 0-9, return string
    std::string addZero();                // convenience: addDigit(0)
    std::string backspace();              // delete rightmost symbol
    std::string clear();                  // set to zero
    std::string getString() const;        // read string
    void setString(const std::string &s); // set string (validate)
    std::string edit(int cmd);            // perform command (0..13), return string

    // formatting constants
    static constexpr char DEC_POINT = '.';
    static constexpr char IMAG_UNIT = 'i';

    // keep minimal public API required by task
private:
    std::string s_;       // stored string, format: <real><sep><imag>i, sep is '+' or '-' (separator is sign of imag)
    void ensure_format(); // validate/normalize s_
    static bool is_digit_char(char c) { return c >= '0' && c <= '9'; }
    // helpers to find separator and parts
    int find_imag_sign_pos() const; // returns index of separator char (+/- between parts), -1 if invalid
    void normalize_empty_parts();   // ensure "0" for empty integer parts
};
