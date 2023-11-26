#pragma once
#include "matrix.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template<typename T>
sq_matrix_t<T> operator+(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    sq_matrix_t<T> res_matrix{lhs.size_};
    for (int i = 0; i < lhs.size_; i++) {
        for (int j = 0; j < lhs.size_; j++) {
            res_matrix[i][j] = lhs[i][j] + rhs[i][j];
        }
    }

    return res_matrix;
}

template<typename T>
sq_matrix_t<T> operator-(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    sq_matrix_t<T> res_matrix{lhs.size_};
    for (int i = 0; i < lhs.size_; i++) {
        for (int j = 0; j < lhs.size_; j++) {
            res_matrix[i][j] = lhs[i][j] - rhs[i][j];
        }
    }

    return res_matrix;
}

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T> operator*(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    sq_matrix_t<T> res_matrix{lhs.size_};
    sq_matrix_t<T> rhs_transpose = rhs.transpose();
    for (int i = 0; i < lhs.size_; i++) {
        for (int j = 0; j < lhs.size_; j++) {
            T mul_of_lines{};
            for (int k = 0; k < lhs.size_; k++) {
                mul_of_lines += (lhs[i][k] * rhs_transpose[j][k]);
            }
            res_matrix[i][j] = mul_of_lines;
        }
    }
    return res_matrix;
}

template<typename T>
sq_matrix_t<T> operator*(const sq_matrix_t<T>& lhs, const T val) {

    sq_matrix_t<T> res_matrix{lhs.size_};
    for (int i = 0; i < lhs.size_; i++) {
        for (int j = 0; j < lhs.size_; j++) {
            res_matrix[i][j] = lhs[i][j] * val;
        }
    }

    return res_matrix;
}

template<typename T>
sq_matrix_t<T> operator*(const T val, const sq_matrix_t<T>& rhs) {

    sq_matrix_t<T> res_matrix{rhs.size_};
    for (int i = 0; i < rhs.size_; i++) {
        for (int j = 0; j < rhs.size_; j++) {
            res_matrix[i][j] = rhs[i][j] * val;
        }
    }
    return res_matrix;
}

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T>& sq_matrix_t<T>::operator=(const sq_matrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    sq_matrix_t<T> tmp_matrix = sq_matrix_t<T>(other);
    delete [] data_;
    data_ = tmp_matrix.data_;
    size_ = tmp_matrix.size_;
}
}
