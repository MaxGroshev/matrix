#pragma once
#include "matrix.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template<typename T>
imatrix_t<T> operator+(const imatrix_t<T>& lhs, const imatrix_t<T>& rhs) {
    if (lhs.row_size_ != rhs.row_size_ && lhs.column_size_ != rhs.column_size_)
        throw mx_exception(mx_exception::MX_ERR::WRONG_SIZES);

    imatrix_t<T> res_matrix{lhs.column_size_, lhs.row_size_};
    for (int i = 0; i < lhs.column_size_; i++) {
        for (int j = 0; j < lhs.row_size_; j++) {
            res_matrix[i][j] = lhs[i][j] + rhs[i][j];
        }
    }

    return res_matrix;
}

template<typename T>
imatrix_t<T> operator-(const imatrix_t<T>& lhs, const imatrix_t<T>& rhs) {
    if (lhs.row_size_ != rhs.row_size_ && lhs.column_size_ != rhs.column_size_)
        throw mx_exception(mx_exception::MX_ERR::WRONG_SIZES);

    imatrix_t<T> res_matrix{lhs.column_size_, lhs.row_size_};
    for (int i = 0; i < lhs.column_size_; i++) {
        for (int j = 0; j < lhs.row_size_; j++) {
            res_matrix[i][j] = lhs[i][j] - rhs[i][j];
        }
    }

    return res_matrix;
}

//-----------------------------------------------------------------------------------------

template<typename T>
imatrix_t<T> operator*(const imatrix_t<T>& lhs, const imatrix_t<T>& rhs) {
    if (lhs.row_size_ != rhs.column_size_)
        throw mx_exception(mx_exception::MX_ERR::WRONG_SIZES);

    imatrix_t<T> res_matrix{lhs.column_size_, rhs.row_size_};
    imatrix_t<T> rhs_transpose = rhs.transpose();
    for (int i = 0; i < lhs.column_size_; i++) {
        for (int j = 0; j < rhs.row_size_; j++) {
            T mul_of_lines{};
            for (int k = 0; k < lhs.row_size_; k++) {
                mul_of_lines += (lhs[i][k] * rhs_transpose[j][k]);
            }
            res_matrix[i][j] = mul_of_lines;
        }
    }
    return res_matrix;
}

template<typename T>
imatrix_t<T> operator*(const imatrix_t<T>& lhs, const T val) {

    imatrix_t<T> res_matrix{lhs.column_size_, lhs.row_size_,};
    for (int i = 0; i < lhs.column_size_; i++) {
        for (int j = 0; j < lhs.row_size_; j++) {
            res_matrix[i][j] = lhs[i][j] * val;
        }
    }

    return res_matrix;
}

template<typename T>
imatrix_t<T> operator*(const T val, const imatrix_t<T>& rhs) {

    imatrix_t<T> res_matrix{rhs.column_size_, rhs.row_size_,};
    for (int i = 0; i < rhs.column_size_; i++) {
        for (int j = 0; j < rhs.row_size_; j++) {
            res_matrix[i][j] = rhs[i][j] * val;
        }
    }
    return res_matrix;
}

//-----------------------------------------------------------------------------------------

template<typename T>
imatrix_t<T>& imatrix_t<T>::operator=(const imatrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    imatrix_t<T> tmp_matrix = imatrix_t<T>(other);
    delete [] data_;
    data_ = tmp_matrix.data_;
    row_size_ = tmp_matrix.row_size_;
    column_size_ = tmp_matrix.column_size_;
}

//-----------------------------------------------------------------------------------------

template<typename T>
int imatrix_t<T>::operator==(const imatrix_t<T>& other) const {
    if (row_size_ == other.row_size_ && column_size_ == other.  column_size_) {
        for (int i = 0; i < row_size_ * column_size_; i++) {
            if (data_[i] != other.data_[i]) {
                return 0;
            }
        }
        return 1;
    }

    return 0;
}

template<typename T>
int imatrix_t<T>::operator!=(const imatrix_t<T>& other) const {
    if (row_size_ == other.row_size_ && column_size_ == other.column_size_) {
        for (int i = 0; i < row_size_ * column_size_; i++) {
            if (data_[i] != other.data_[i]) {
                return 1;
            }
        }
        return 0;
    }

    return 1;
}


}
