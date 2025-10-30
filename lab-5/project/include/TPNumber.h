#pragma once
#include <string>
#include <stdexcept>

class TPException : public std::runtime_error
{
public:
    explicit TPException(const std::string &s) : std::runtime_error(s) {}
};

class TPNumber
{
public:
    // Constructors
    TPNumber(long double a, int base, int precision);            // from real
    TPNumber(const std::string &a_str, int base, int precision); // from string (a_str is representation in base)
    TPNumber(const TPNumber &other) = default;

    // arithmetic (require same base and precision)
    TPNumber Add(const TPNumber &d) const;
    TPNumber Sub(const TPNumber &d) const;
    TPNumber Mul(const TPNumber &d) const;
    TPNumber Div(const TPNumber &d) const;

    // unary
    TPNumber Invert() const; // 1 / n
    TPNumber Square() const; // n*n

    // accessors
    long double GetNumber() const;
    std::string GetString() const;

    int GetBaseNumber() const;
    std::string GetBaseString() const;

    int GetPrecisionNumber() const;
    std::string GetPrecisionString() const;

    // mutators (validate). They change base/precision and re-round value appropriately.
    void SetBaseNumber(int newb);
    void SetBaseString(const std::string &bs);

    void SetPrecisionNumber(int newc);
    void SetPrecisionString(const std::string &newc);

private:
    long double n_; // stored numeric value (rounded to current base/precision)
    int b_;         // base (2..16)
    int c_;         // precision (>=0)

    // helpers
    void validate_base(int b) const;
    void validate_precision(int c) const;
    static int digit_value(char ch);
    static char digit_char(int v);

    // rounding to base b with c fractional digits (in-place adjust n_)
    void round_to_precision();
    // parse string a_str expressed in base b_ into long double (does not round)
    static long double parse_base_string(const std::string &s, int base);
    // convert given scaled integer representation (rounding applied via round_to_precision) to string
    std::string number_to_base_string() const;
};
