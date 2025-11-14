#pragma once
#include <set>
#include <vector>
#include <stdexcept>
#include <iterator>
#include <algorithm>

// Вариант 1: наследование от std::set<T>
template <typename T>
class tset_inherit : public std::set<T>
{
public:
    using base = std::set<T>;
    tset_inherit() = default;

    void Clear() { this->clear(); }
    void Add(const T &d) { this->insert(d); }
    void Remove(const T &d) { this->erase(d); }
    bool Empty() const { return this->empty(); }
    bool Contains(const T &d) const { return this->find(d) != this->end(); }
    std::size_t Count() const { return this->size(); }

    // Element by 1-based index (read-only). Throws std::out_of_range.
    T Element(std::size_t j) const
    {
        if (j < 1 || j > Count())
            throw std::out_of_range("Element index");
        auto it = this->begin();
        std::advance(it, j - 1);
        return *it;
    }

    // Set operations returning new tset_inherit
    tset_inherit Union(const tset_inherit &q) const
    {
        tset_inherit res = *this;
        res.insert(q.begin(), q.end());
        return res;
    }
    tset_inherit Difference(const tset_inherit &q) const
    {
        tset_inherit res;
        for (const auto &x : *this)
            if (q.find(x) == q.end())
                res.insert(x);
        return res;
    }
    tset_inherit Intersect(const tset_inherit &q) const
    {
        tset_inherit res;
        for (const auto &x : *this)
            if (q.find(x) != q.end())
                res.insert(x);
        return res;
    }
};

// Вариант 2: композиция (обёртка)
template <typename T>
class tset_wrap
{
private:
    std::set<T> data;

public:
    tset_wrap() = default;

    void Clear() { data.clear(); }
    void Add(const T &d) { data.insert(d); }
    void Remove(const T &d) { data.erase(d); }
    bool Empty() const { return data.empty(); }
    bool Contains(const T &d) const { return data.find(d) != data.end(); }
    std::size_t Count() const { return data.size(); }

    T Element(std::size_t j) const
    {
        if (j < 1 || j > Count())
            throw std::out_of_range("Element index");
        auto it = data.begin();
        std::advance(it, j - 1);
        return *it;
    }

    tset_wrap Union(const tset_wrap &q) const
    {
        tset_wrap res;
        res.data = data;
        res.data.insert(q.data.begin(), q.data.end());
        return res;
    }
    tset_wrap Difference(const tset_wrap &q) const
    {
        tset_wrap res;
        for (const auto &x : data)
            if (q.data.find(x) == q.data.end())
                res.data.insert(x);
        return res;
    }
    tset_wrap Intersect(const tset_wrap &q) const
    {
        tset_wrap res;
        for (const auto &x : data)
            if (q.data.find(x) != q.data.end())
                res.data.insert(x);
        return res;
    }
};
