#include "pch.h"
#include "Matrix.h"

#include <thread>
#include <algorithm>



Matrix::Matrix(int rows, int cols)
    : rows_(rows), cols_(cols), data_(rows* cols, 0.0)
{
    if (rows <= 0 || cols <= 0)
        throw std::invalid_argument("Rows and columns must be positive");
}

void Matrix::setValue(int row, int col, double value)
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Index out of range");

    data_[row * cols_ + col] = value;
}

void Matrix::setValues(const std::vector<double>& values)
{
    if (values.size() != static_cast<size_t>(rows_ * cols_))
        throw std::out_of_range("Wrong number of values");

    data_ = values;
}

double Matrix::getValue(int row, int col) const
{
    if (row < 0 || row >= rows_ || col < 0 || col >= cols_)
        throw std::out_of_range("Index out of range");

    return data_[row * cols_ + col];
}

int Matrix::getRows() const
{
    return rows_;
}

int Matrix::getCols() const
{
    return cols_;
}




Matrix Matrix::operator+(const Matrix& other) const
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
        throw std::invalid_argument("Matrices must have the same dimensions");

    Matrix result(rows_, cols_);

    const size_t total = static_cast<size_t>(rows_) * cols_;
    const unsigned hw = std::thread::hardware_concurrency();
	std::cout << "Hardware concurrency: " << hw << std::endl;
    const unsigned numThreads = std::max(1u, std::min<unsigned>(hw == 0 ? 4 : hw, static_cast<unsigned>(total)));

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    auto worker = [this, &other, &result](size_t begin, size_t end)
        {
            for (size_t idx = begin; idx < end; ++idx)
            {
                result.data_[idx] = data_[idx] + other.data_[idx];
            }
        };

    size_t chunkSize = total / numThreads;
    size_t remainder = total % numThreads;
    size_t begin = 0;

    for (unsigned t = 0; t < numThreads; ++t)
    {
        size_t extra = (t < remainder) ? 1 : 0;
        size_t end = begin + chunkSize + extra;

        threads.emplace_back(worker, begin, end);
        begin = end;
    }

    for (auto& th : threads)
    {
        th.join();
    }

    return result;
}

Matrix Matrix::operator-(const Matrix& other) const 
{
    if (rows_ != other.rows_ || cols_ != other.cols_)
    {
        throw std::invalid_argument("Matrices must have the same dimensions");
    }
    Matrix result(rows_, cols_);
    for (int i = 0; i < rows_; ++i)
    {
        for (int j = 0; j < cols_; ++j)
        {
            result.setValue(i, j, getValue(i, j) - other.getValue(i, j));
        }
    }
    return result;
}

