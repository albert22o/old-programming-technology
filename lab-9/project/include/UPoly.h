#pragma once
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <algorithm>

struct TMember
{
    int coeff;
    int degree;
    TMember(int c = 0, int d = 0) : coeff(c), degree(d) {}
    int Degree() const { return (coeff == 0) ? 0 : degree; } // for zero-member degree treated as 0 by spec
    void SetDegree(int d) { degree = d; }
    void SetCoeff(int c) { coeff = c; }
    bool operator==(const TMember &other) const
    {
        return coeff == other.coeff && degree == other.degree;
    }
    // string representation "cx^d" minimal
    std::string ToString() const
    {
        std::ostringstream os;
        os << coeff << "*X^" << degree;
        return os.str();
    }
    // derivative of single term
    TMember Diff() const
    {
        if (coeff == 0 || degree == 0)
            return TMember(0, 0);
        return TMember(coeff * degree, degree - 1);
    }
    double Eval(double x) const
    {
        return coeff * std::pow(x, degree);
    }
};

class TPoly
{
private:
    // normalized: degrees in descending order, no zero coeffs (except zero polynomial has empty vector or single zero)
    std::vector<TMember> members;

    void Normalize()
    {
        if (members.empty())
            return;
        // combine like degrees using map on stack
        std::sort(members.begin(), members.end(), [](const TMember &a, const TMember &b)
                  { return a.degree > b.degree; });
        std::vector<TMember> out;
        for (const auto &m : members)
        {
            if (m.coeff == 0)
                continue;
            if (!out.empty() && out.back().degree == m.degree)
            {
                out.back().coeff += m.coeff;
            }
            else
            {
                out.push_back(m);
            }
        }
        // remove any zeros resulted from combining
        std::vector<TMember> finalv;
        for (auto &m : out)
            if (m.coeff != 0)
                finalv.push_back(m);
        members.swap(finalv);
    }

public:
    // constructors
    TPoly() = default; // zero polynomial
    TPoly(int c, int d)
    {
        if (c != 0)
            members.emplace_back(c, d);
        Normalize();
    }

    // copy & move default are fine

    // Degree: degree of polynomial (0 for zero polynomial)
    int Degree() const
    {
        if (members.empty())
            return 0;
        return members.front().degree;
    }

    // Coeff(n): coefficient at degree n, 0 if absent
    int Coeff(int n) const
    {
        for (const auto &m : members)
            if (m.degree == n)
                return m.coeff;
        return 0;
    }

    // Clear
    void Clear() { members.clear(); }

    // Access element by index (0..count-1) to read coeff and degree
    int Count() const { return static_cast<int>(members.size()); }
    const TMember &Element(int i) const
    {
        if (i < 0 || i >= Count())
            throw std::out_of_range("Element index");
        return members[i];
    }

    // equality
    bool operator==(const TPoly &q) const
    {
        // normalized invariant -> direct compare
        return members == q.members;
    }

    // unary minus
    TPoly operator-() const
    {
        TPoly res = *this;
        for (auto &m : res.members)
            m.coeff = -m.coeff;
        // normalization not needed
        return res;
    }

    // addition
    TPoly operator+(const TPoly &q) const
    {
        TPoly res;
        res.members = members;
        res.members.insert(res.members.end(), q.members.begin(), q.members.end());
        res.Normalize();
        return res;
    }

    // subtraction
    TPoly operator-(const TPoly &q) const
    {
        TPoly res;
        res.members = members;
        for (auto m : q.members)
        {
            m.coeff = -m.coeff;
            res.members.push_back(m);
        }
        res.Normalize();
        return res;
    }

    // multiplication
    TPoly operator*(const TPoly &q) const
    {
        TPoly res;
        if (members.empty() || q.members.empty())
            return res; // zero
        std::vector<TMember> tmp;
        tmp.reserve(members.size() * q.members.size());
        for (const auto &a : members)
            for (const auto &b : q.members)
                tmp.emplace_back(a.coeff * b.coeff, a.degree + b.degree);
        res.members = std::move(tmp);
        res.Normalize();
        return res;
    }

    // derivative
    TPoly Diff() const
    {
        TPoly res;
        for (const auto &m : members)
        {
            TMember d = m.Diff();
            if (d.coeff != 0)
                res.members.push_back(d);
        }
        res.Normalize();
        return res;
    }

    // Evaluate at x
    double Eval(double x) const
    {
        double sum = 0.0;
        for (const auto &m : members)
            sum += m.Eval(x);
        return sum;
    }

    // Add single term (helper used in tests / building)
    void AddTerm(int c, int d)
    {
        if (c == 0)
            return;
        members.emplace_back(c, d);
        Normalize();
    }

    // ToString minimal
    std::string ToString() const
    {
        if (members.empty())
            return "0";
        std::ostringstream os;
        bool first = true;
        for (const auto &m : members)
        {
            if (!first)
                os << " + ";
            os << m.ToString();
            first = false;
        }
        return os.str();
    }
};
