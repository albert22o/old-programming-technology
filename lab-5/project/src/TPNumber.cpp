#include "TPNumber.h"
#include <cmath>
#include <cctype>
#include <limits>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <climits>

static inline long double pow_int(int base, int exp)
{
    long double r = 1.0L;
    for (int i = 0; i < exp; ++i)
        r *= (long double)base;
    return r;
}

TPNumber::TPNumber(long double a, int base, int precision)
    : n_(a), b_(base), c_(precision)
{
    validate_base(b_);
    validate_precision(c_);
    round_to_precision();
}

TPNumber::TPNumber(const std::string &a_str, int base, int precision)
    : n_(0.0L), b_(base), c_(precision)
{
    validate_base(b_);
    validate_precision(c_);
    n_ = parse_base_string(a_str, b_);
    round_to_precision();
}

void TPNumber::validate_base(int b) const
{
    if (b < 2 || b > 16)
        throw TPException("base out of range");
}
void TPNumber::validate_precision(int c) const
{
    if (c < 0)
        throw TPException("precision must be >= 0");
}

int TPNumber::digit_value(char ch)
{
    if ('0' <= ch && ch <= '9')
        return ch - '0';
    if ('A' <= ch && ch <= 'F')
        return 10 + (ch - 'A');
    if ('a' <= ch && ch <= 'f')
        return 10 + (ch - 'a');
    return -1;
}
char TPNumber::digit_char(int v)
{
    if (v >= 0 && v <= 9)
        return '0' + v;
    return 'A' + (v - 10);
}

long double TPNumber::parse_base_string(const std::string &s, int base)
{
    // Accept optional leading '+'/'-' and optional point '.'
    if (s.empty())
        throw TPException("empty string");
    size_t i = 0;
    bool neg = false;
    if (s[0] == '+' || s[0] == '-')
    {
        neg = (s[0] == '-');
        i = 1;
    }
    // split integer and fractional
    size_t p = s.find('.', i);
    std::string intpart = (p == std::string::npos) ? s.substr(i) : s.substr(i, p - i);
    std::string fracpart = (p == std::string::npos) ? std::string() : s.substr(p + 1);

    long double val = 0.0L;
    // integer part
    for (char ch : intpart)
    {
        if (ch == '\0')
            continue;
        int dv = digit_value(ch);
        if (dv < 0 || dv >= base)
            throw TPException("invalid digit in integer part");
        val = val * base + dv;
    }
    // fractional
    long double denom = base;
    for (char ch : fracpart)
    {
        int dv = digit_value(ch);
        if (dv < 0 || dv >= base)
            throw TPException("invalid digit in fractional part");
        val += dv / denom;
        denom *= base;
    }
    return neg ? -val : val;
}

void TPNumber::round_to_precision()
{
    // scale = b_^c_
    long double scale_ld = pow_int(b_, c_);
    // scaled = round(n_ * scale)
    long double scaled_ld = std::round(n_ * scale_ld);
    // avoid huge overflow when converting to integer: keep as long double for recomposition
    n_ = scaled_ld / scale_ld;
}

std::string TPNumber::number_to_base_string() const
{
    // Represent using rounding consistent with round_to_precision (use scaled integer)
    long double scale_ld = pow_int(b_, c_);
    long double scaled_ld = std::round(n_ * scale_ld);
    // extract sign
    bool neg = (scaled_ld < 0);
    unsigned long long scaled_abs;
    // clamp to unsigned long long safely
    long double tmp = llabs(scaled_ld);
    if (tmp > (long double)ULLONG_MAX)
        throw TPException("value too large to stringify");
    scaled_abs = static_cast<unsigned long long>(tmp + 0.5L);

    unsigned long long scale_u = 1;
    for (int i = 0; i < c_; ++i)
    {
        // safe multiply
        if (scale_u > ULLONG_MAX / (unsigned)b_)
        {
            // fallback to string via integer and fractional loops (unlikely for reasonable c)
            // but we'll still attempt with long double method:
            std::ostringstream os; // fallback: show decimal representation
            if (neg)
                os << '-';
            os.setf(std::ios::fmtflags(0), std::ios::floatfield);
            os << std::fixed << (double)n_;
            return os.str();
        }
        scale_u *= (unsigned)b_;
    }

    unsigned long long ipart = (scale_u == 0) ? 0 : (scaled_abs / scale_u);
    unsigned long long frac_scaled = (scale_u == 0) ? 0 : (scaled_abs % scale_u);

    // integer digits
    if (ipart == 0)
    {
        // zero
    }
    std::string intdigits;
    unsigned long long tmp_ip = ipart;
    if (tmp_ip == 0)
        intdigits = "0";
    else
    {
        while (tmp_ip > 0)
        {
            int d = static_cast<int>(tmp_ip % (unsigned long long)b_);
            intdigits.push_back(digit_char(d));
            tmp_ip /= (unsigned long long)b_;
        }
        std::reverse(intdigits.begin(), intdigits.end());
    }

    // fractional digits (exactly c_ digits, leading zeros)
    std::string fracdigits;
    if (c_ > 0)
    {
        unsigned long long tmp_frac = frac_scaled;
        // generate digits from least significant by repeated division may be tricky; instead produce from highest place:
        // produce digits by dividing by base^(c-1-i)
        unsigned long long place = 1;
        for (int i = 0; i < c_; ++i)
        {
            // compute place = b_^(c_-1-i)
        }
        // simpler: build from least significant then reverse with padding
        for (int i = 0; i < c_; ++i)
        {
            int d = static_cast<int>(tmp_frac % (unsigned long long)b_);
            fracdigits.push_back(digit_char(d));
            tmp_frac /= (unsigned long long)b_;
        }
        while ((int)fracdigits.size() < c_)
            fracdigits.push_back('0');
        std::reverse(fracdigits.begin(), fracdigits.end());
    }

    std::ostringstream os;
    if (neg)
        os << '-';
    os << intdigits;
    if (c_ > 0)
    {
        os << '.';
        os << fracdigits;
    }
    return os.str();
}

// arithmetic helpers: check base/precision match
static inline void require_same_base_precision(const TPNumber &a, const TPNumber &b)
{
    if (a.GetBaseNumber() != b.GetBaseNumber() || a.GetPrecisionNumber() != b.GetPrecisionNumber())
        throw TPException("base/precision mismatch");
}

TPNumber TPNumber::Add(const TPNumber &d) const
{
    require_same_base_precision(*this, d);
    return TPNumber(n_ + d.n_, b_, c_);
}
TPNumber TPNumber::Sub(const TPNumber &d) const
{
    require_same_base_precision(*this, d);
    return TPNumber(n_ - d.n_, b_, c_);
}
TPNumber TPNumber::Mul(const TPNumber &d) const
{
    require_same_base_precision(*this, d);
    return TPNumber(n_ * d.n_, b_, c_);
}
TPNumber TPNumber::Div(const TPNumber &d) const
{
    require_same_base_precision(*this, d);
    if (std::fabs(d.n_) < std::numeric_limits<long double>::epsilon())
        throw TPException("division by zero");
    return TPNumber(n_ / d.n_, b_, c_);
}

TPNumber TPNumber::Invert() const
{
    if (std::fabs(n_) < std::numeric_limits<long double>::epsilon())
        throw TPException("invert: zero");
    return TPNumber(1.0L / n_, b_, c_);
}
TPNumber TPNumber::Square() const
{
    return TPNumber(n_ * n_, b_, c_);
}

long double TPNumber::GetNumber() const { return n_; }

std::string TPNumber::GetString() const { return number_to_base_string(); }

int TPNumber::GetBaseNumber() const { return b_; }
std::string TPNumber::GetBaseString() const { return std::to_string(b_); }

int TPNumber::GetPrecisionNumber() const { return c_; }
std::string TPNumber::GetPrecisionString() const { return std::to_string(c_); }

void TPNumber::SetBaseNumber(int newb)
{
    validate_base(newb);
    b_ = newb;
    // rounding to same c_ but new base
    round_to_precision();
}
void TPNumber::SetBaseString(const std::string &bs)
{
    int nb = 0;
    try
    {
        nb = std::stoi(bs);
    }
    catch (...)
    {
        throw TPException("invalid base string");
    }
    SetBaseNumber(nb);
}
void TPNumber::SetPrecisionNumber(int newc)
{
    validate_precision(newc);
    c_ = newc;
    round_to_precision();
}
void TPNumber::SetPrecisionString(const std::string &newc)
{
    int nc = 0;
    try
    {
        nc = std::stoi(newc);
    }
    catch (...)
    {
        throw TPException("invalid precision string");
    }
    SetPrecisionNumber(nc);
}
