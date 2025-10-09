#include "Matrix.h"
#include <sstream>
#include <limits>
#include <algorithm>

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols)
{
    if (rows <= 0)
        throw MyException("Invalid number of rows = " + std::to_string(rows));
    if (cols <= 0)
        throw MyException("Invalid number of cols = " + std::to_string(cols));
    data_.assign(static_cast<size_t>(rows_) * cols_, 0);
}

void Matrix::check_indices(int i, int j) const
{
    if (i < 0 || i >= rows_)
        throw MyException("Index i out of range: " + std::to_string(i));
    if (j < 0 || j >= cols_)
        throw MyException("Index j out of range: " + std::to_string(j));
}

int Matrix::get(int i, int j) const
{
    check_indices(i, j);
    return data_[static_cast<size_t>(index(i, j))];
}

void Matrix::set(int i, int j, int value)
{
    check_indices(i, j);
    data_[static_cast<size_t>(index(i, j))] = value;
}

Matrix Matrix::operator+(const Matrix &b) const
{
    if (rows_ != b.rows_ || cols_ != b.cols_)
        throw MyException("Dimension mismatch for addition");
    Matrix c(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            c.data_[static_cast<size_t>(index(i, j))] = data_[static_cast<size_t>(index(i, j))] + b.data_[static_cast<size_t>(b.index(i, j))];
    return c;
}

Matrix Matrix::operator-(const Matrix &b) const
{
    if (rows_ != b.rows_ || cols_ != b.cols_)
        throw MyException("Dimension mismatch for subtraction");
    Matrix c(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            c.data_[static_cast<size_t>(index(i, j))] = data_[static_cast<size_t>(index(i, j))] - b.data_[static_cast<size_t>(b.index(i, j))];
    return c;
}

Matrix Matrix::operator*(const Matrix &b) const
{
    if (cols_ != b.rows_)
        throw MyException("Dimension mismatch for multiplication");
    Matrix c(rows_, b.cols_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < b.cols_; ++j)
        {
            long long sum = 0;
            for (int k = 0; k < cols_; ++k)
            {
                sum += static_cast<long long>(get(i, k)) * b.get(k, j);
            }
            c.set(i, j, static_cast<int>(sum)); // assume fits int for lab task
        }
    }
    return c;
}

bool Matrix::operator==(const Matrix &b) const
{
    if (rows_ != b.rows_ || cols_ != b.cols_)
        throw MyException("Dimension mismatch for equality");
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            if (get(i, j) != b.get(i, j))
                return false;
    return true;
}

Matrix Matrix::Transp() const
{
    if (rows_ != cols_)
        throw MyException("Transpose requires square matrix");
    Matrix t(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
        for (int j = 0; j < cols_; ++j)
            t.set(j, i, get(i, j));
    return t;
}

int Matrix::Min() const
{
    if (data_.empty())
        throw MyException("Empty matrix has no minimum");
    int mn = std::numeric_limits<int>::max();
    for (int v : data_)
        if (v < mn)
            mn = v;
    return mn;
}

std::string Matrix::ToString() const
{
    std::ostringstream oss;
    oss << "{";
    for (int i = 0; i < rows_; ++i)
    {
        oss << "{";
        for (int j = 0; j < cols_; ++j)
        {
            oss << get(i, j);
            if (j + 1 < cols_)
                oss << ",";
        }
        oss << "}";
        if (i + 1 < rows_)
            oss << ",";
    }
    oss << "}";
    return oss.str();
}
