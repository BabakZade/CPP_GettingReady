#pragma once
#include <vector>
#include <stdexcept>
#include <iostream>

#ifdef MATRIXLAB_EXPORTS
#define MATRIX_API __declspec(dllexport)
#else
#define MATRIX_API __declspec(dllimport)
#endif

class Matrix
{
public:
    Matrix(int rows, int cols);

    void setValue(int row, int col, double value);
    void setValues(const std::vector<double>& values);
    double getValue(int row, int col) const;

    int getRows() const;
    int getCols() const;


	Matrix operator+(const Matrix& other) const;

    Matrix operator-(const Matrix& other) const;

private:
    int rows_;
    int cols_;
    std::vector<double> data_;
};