#pragma once
#include <vector>
#include <stdexcept>
#include <string>

class MyException : public std::runtime_error
{
public:
    explicit MyException(const std::string &s) : std::runtime_error(s) {}
};

class Matrix
{
public:
    // Конструктор: принимает число строк i и столбцов j, оба > 0
    Matrix(int rows, int cols);

    // Индексатор: доступ и запись элемента [i,j]
    int get(int i, int j) const;
    void set(int i, int j, int value);

    // свойства: число строк и столбцов
    int I() const { return rows_; }
    int J() const { return cols_; }

    // Операции
    Matrix operator+(const Matrix &b) const;
    Matrix operator-(const Matrix &b) const;
    Matrix operator*(const Matrix &b) const; // matrix multiplication
    bool operator==(const Matrix &b) const;
    bool operator!=(const Matrix &b) const { return !(*this == b); }

    // Транспонировать (требование: квадратная матрица)
    Matrix Transp() const;

    // Минимальный элемент
    int Min() const;

    // Преобразование в строку "{{1,2},{3,4}}"
    std::string ToString() const;

private:
    int rows_;
    int cols_;
    std::vector<int> data_; // row-major: data_[i*cols_ + j]

    void check_indices(int i, int j) const;
    int index(int i, int j) const { return i * cols_ + j; }
};
