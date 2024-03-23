#include <iostream>
#include <string>
#include <stdexcept> // std::out_of_range()
#include <iomanip>   // std::setw()

using namespace std;

#include "matrix.h"

#ifndef _MSC_FULL_VER // if not Visual Studio Compiler
    #warning "Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym"
#else
    #pragma message ("Klasa jest do zaimplementowania. Instrukcja w pliku naglowkowym")
#endif

TwoDimensionMatrix::TwoDimensionMatrix() {
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = 0;
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const TwoDimensionMatrix &copy_matrix) {
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = copy_matrix.matrix_[i][j];
        }
    }
}

TwoDimensionMatrix::TwoDimensionMatrix(const MatrixElement matrix[size_][size_]) {
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
            matrix_[i][j] = matrix[i][j];
        }
    }
}

std::size_t TwoDimensionMatrix::get(std::size_t row, std::size_t column) const{
    return matrix_[row][column];
}

TwoDimensionMatrix& TwoDimensionMatrix::operator=(const TwoDimensionMatrix &other) {
    if (this != &other) {
        for (std::size_t i = 0; i < size_; ++i) {
            for (std::size_t j = 0; j < size_; ++j) {
                matrix_[i][j] = other.matrix_[i][j];
            }
        }
    }
    return *this;
}

const MatrixElement *TwoDimensionMatrix::operator[](size_t i) const{
    return matrix_[i];
}
MatrixElement *TwoDimensionMatrix::operator[](size_t i){
    return matrix_[i];
}

ostream& operator<<(ostream &stream, const TwoDimensionMatrix& matrix)
{
    for (size_t i = 0; i < TwoDimensionMatrix::size(); ++i) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); ++j) {
            stream << matrix.get(i, j) << " ";
        }
    }
    return stream;
}
istream& operator>>(istream &stream, TwoDimensionMatrix& matrix) {
    for (size_t i = 0; i < TwoDimensionMatrix::size(); ++i) {
        for (size_t j = 0; j < TwoDimensionMatrix::size(); ++j) {
            stream >> matrix.matrix_[i][j];
        }
    }
    return stream;
}
TwoDimensionMatrix operator+(const TwoDimensionMatrix& matrix1, const TwoDimensionMatrix& matrix2){
    TwoDimensionMatrix added_matrix;
    std::size_t size_of_arr = TwoDimensionMatrix::size();
    for (size_t i = 0; i < size_of_arr; i++) {
        for (size_t j = 0; j < size_of_arr; ++j) {
            added_matrix.matrix_[i][j] = matrix1.matrix_[i][j] + matrix2.matrix_[i][j];
        }
    }
    return added_matrix;
}

TwoDimensionMatrix &TwoDimensionMatrix::operator*=(MatrixElement number) {
    std::size_t size_of_arr = TwoDimensionMatrix::size();
    for (size_t i = 0; i < size_of_arr; i++) {
        for (size_t j = 0; j < size_of_arr; ++j) {
            matrix_[i][j]*=number;
        }
    }
    return *this;
}

TwoDimensionMatrix TwoDimensionMatrix::operator&&(const TwoDimensionMatrix &matrix) const {
    TwoDimensionMatrix compared_matrix;
    std::size_t size_of_arr = TwoDimensionMatrix::size();
    for (size_t i = 0; i < size_of_arr; i++) {
        for (size_t j = 0; j < size_of_arr; ++j) {
            compared_matrix.matrix_[i][j] = matrix_[i][j] && matrix.matrix_[i][j];
        }
    }
    return compared_matrix;
}