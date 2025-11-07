#pragma once
#include <string>
#include <stdexcept>

enum MemState
{
    _Off,
    _On
};

template <class T>
class TMemory
{
private:
    T FNumber;
    MemState FState;

public:
    // Конструктор
    TMemory() : FNumber(T()), FState(_Off) {}

    // Записать (Store)
    void Store(const T &E)
    {
        FNumber = E;
        FState = _On;
    }

    // Добавить (Add)
    void Add(const T &E)
    {
        FNumber = FNumber + E;
        FState = _On;
    }

    // Очистить (Clear)
    void Clear()
    {
        FNumber = T();
        FState = _Off;
    }

    // Прочитать состояние (_On/_Off)
    std::string ReadState() const
    {
        return (FState == _On) ? "_On" : "_Off";
    }

    // Прочитать значение
    T ReadNumber() const
    {
        return FNumber;
    }
};
