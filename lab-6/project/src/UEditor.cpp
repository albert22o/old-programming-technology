#include "UEditor.h"
#include <algorithm>
#include <cctype>
#include <cmath>

TEditor::TEditor() : s_("0+0i") {}

int TEditor::find_imag_sign_pos() const
{
    // find '+' or '-' that separates real and imag. Skip leading sign at position 0.
    for (size_t i = 1; i < s_.size(); ++i)
    {
        if ((s_[i] == '+' || s_[i] == '-') && i + 1 < s_.size())
        {
            // ensure there is an 'i' at the end (basic check)
            auto pos_i = s_.rfind(IMAG_UNIT);
            if (pos_i != std::string::npos && pos_i > i)
                return static_cast<int>(i);
        }
    }
    return -1;
}

void TEditor::normalize_empty_parts()
{
    // ensure parts are not empty (e.g., "-.5+ i" -> set zeros)
    int sep = find_imag_sign_pos();
    if (sep < 0)
        return;
    std::string real = s_.substr(0, sep);
    std::string imag = s_.substr(sep + 1, s_.size() - (sep + 2)); // exclude trailing 'i'
    if (real.empty() || real == "+" || real == "-")
    {
        real = "0";
    }
    if (imag.empty())
        imag = "0";
    s_ = real + s_[sep] + imag + IMAG_UNIT;
}

void TEditor::ensure_format()
{
    // minimal validation and normalization: must end with 'i', contain separator, parts valid chars
    if (s_.empty())
    {
        s_ = "0+0i";
        return;
    }
    if (s_.back() != IMAG_UNIT)
        throw TEditorException("invalid format: missing 'i'");
    int sep = find_imag_sign_pos();
    if (sep < 0)
        throw TEditorException("invalid format: missing separator");
    // split
    std::string real = s_.substr(0, sep);
    std::string imag = s_.substr(sep + 1, s_.size() - (sep + 2)); // exclude 'i'
    if (real.empty())
        real = "0";
    // validate characters: optional leading sign in real, digits and at most one point
    auto validate_part = [](const std::string &part, bool allow_leading_sign)
    {
        bool seen_point = false;
        if (part.empty())
            return false;
        size_t i = 0;
        if (allow_leading_sign && (part[0] == '+' || part[0] == '-'))
        {
            if (part.size() == 1)
                return false;
            i = 1;
        }
        for (; i < part.size(); ++i)
        {
            char c = part[i];
            if (c == DEC_POINT)
            {
                if (seen_point)
                    return false;
                seen_point = true;
            }
            else if (!is_digit_char(c))
                return false;
        }
        return true;
    };
    if (!validate_part(real, true) || !validate_part(imag, false))
        throw TEditorException("invalid numeric parts");
    normalize_empty_parts();
}

bool TEditor::isZero() const
{
    // parse numeric zero for both real and imaginary
    try
    {
        // make copies to avoid throwing outward
        std::string s = s_;
        if (s.empty() || s.back() != IMAG_UNIT)
            return false;
        int sep = find_imag_sign_pos();
        if (sep < 0)
            return false;
        std::string real = s.substr(0, sep);
        std::string imag = s.substr(sep + 1, s.size() - (sep + 2));
        auto parse = [](const std::string &p) -> long double
        {
            if (p.empty())
                return 0.0L;
            return std::stold(p);
        };
        long double r = parse(real);
        long double im = parse(imag);
        return (std::fabs(r) < 1e-18L) && (std::fabs(im) < 1e-18L);
    }
    catch (...)
    {
        return false;
    }
}

std::string TEditor::addSign()
{
    // toggle sign of imaginary part: '+' <-> '-'
    int sep = find_imag_sign_pos();
    if (sep < 0)
    {
        ensure_format();
        sep = find_imag_sign_pos();
        if (sep < 0)
            throw TEditorException("format error");
    }
    s_[sep] = (s_[sep] == '+') ? '-' : '+';
    return s_;
}

std::string TEditor::addDigit(int d)
{
    if (d < 0 || d > 9)
        throw TEditorException("digit out of range");
    // append digit to imaginary part (before final 'i')
    if (s_.empty())
        s_ = "0+0i";
    if (s_.back() != IMAG_UNIT)
        throw TEditorException("invalid format");
    int sep = find_imag_sign_pos();
    if (sep < 0)
        throw TEditorException("invalid format");
    size_t imag_start = sep + 1;
    size_t imag_len = s_.size() - imag_start - 1; // exclude 'i'
    std::string imag = s_.substr(imag_start, imag_len);
    // if imag is "0" replace it unless contains decimal point
    if (imag == "0")
    {
        imag = std::string(1, char('0' + d));
    }
    else
    {
        imag.push_back(char('0' + d));
    }
    s_ = s_.substr(0, imag_start) + imag + IMAG_UNIT;
    return s_;
}

std::string TEditor::addZero()
{
    return addDigit(0);
}

std::string TEditor::backspace()
{
    // delete rightmost editable char before 'i' primarily from imaginary part, otherwise from separator/real
    if (s_.empty())
    {
        s_ = "0+0i";
        return s_;
    }
    if (s_.back() != IMAG_UNIT)
        throw TEditorException("invalid format");
    int sep = find_imag_sign_pos();
    if (sep < 0)
        throw TEditorException("invalid format");
    size_t imag_start = sep + 1;
    size_t imag_len = s_.size() - imag_start - 1;
    if (imag_len > 0)
    {
        // remove last char of imag
        std::string imag = s_.substr(imag_start, imag_len - 1);
        if (imag.empty())
            imag = "0";
        s_ = s_.substr(0, imag_start) + imag + IMAG_UNIT;
        return s_;
    }
    // imag is single char -> remove imag and separator: make imag "0" and try to remove from real
    // remove separator if real can be shortened
    // try to remove last char of real (but keep at least one digit)
    std::string real = s_.substr(0, sep);
    if (real.empty())
        real = "0";
    if (real.size() > 1)
    {
        real.pop_back();
        if (real == "+" || real == "-")
            real = "0";
    }
    else
    {
        real = "0";
    }
    s_ = real + "+" + std::string("0") + IMAG_UNIT;
    return s_;
}

std::string TEditor::clear()
{
    s_ = "0+0i";
    return s_;
}

std::string TEditor::getString() const { return s_; }

void TEditor::setString(const std::string &s)
{
    s_ = s;
    ensure_format();
}

std::string TEditor::edit(int cmd)
{
    if (cmd >= 0 && cmd <= 9)
        return addDigit(cmd);
    switch (cmd)
    {
    case CMD_ADD_SIGN:
        return addSign();
    case CMD_ADD_POINT:
    {
        // add decimal point to imaginary part (if not present)
        int sep = find_imag_sign_pos();
        if (sep < 0)
            throw TEditorException("invalid format");
        size_t imag_start = sep + 1;
        size_t imag_len = s_.size() - imag_start - 1;
        std::string imag = s_.substr(imag_start, imag_len);
        if (imag.find(DEC_POINT) == std::string::npos)
        {
            imag.push_back(DEC_POINT);
            // if imag was "0", keep it as "0."
            s_ = s_.substr(0, imag_start) + imag + IMAG_UNIT;
        }
        return s_;
    }
    case CMD_BACKSPACE:
        return backspace();
    case CMD_CLEAR:
        return clear();
    default:
        throw TEditorException("unknown edit command");
    }
}
