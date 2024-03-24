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

template<typename mx>
mx raise_to_power(const mx& m, int power) {
    if (power <= 1)
        return mx {m};

    std::vector<mx> buf_of_mx {};
    buf_of_mx.push_back(m);

    buf_of_mx.push_back(m * m);
    mx ret_matrix{m * m};

    for (int i = 2; i < power;) {
        if (i + i <= power) {
            ret_matrix = buf_of_mx.back() * buf_of_mx.back();
            buf_of_mx.push_back(ret_matrix);
            i += i;
        }
        else {
            int j = 1;
            int cnt = 0;
            do {
                j *= 2;
                cnt++;
            } while (j + i < power);

            ret_matrix = ret_matrix * buf_of_mx [cnt - 1];
            i += cnt;
        }
    }
    return ret_matrix;
}

//-----------------------------------------------------------------------------------------

template<typename T>
imatrix_t<T>& imatrix_t<T>::operator=(const imatrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    //std::clog << "Copy Assign matrix" << std::endl;
    imatrix_t<T> tmp_matrix {other};
    std::swap(data_, tmp_matrix.data_);
    row_size_ = tmp_matrix.row_size_;
    column_size_ = tmp_matrix.column_size_;

    return *this;
}

//-----------------------------------------------------------------------------------------

template<typename T>
int imatrix_t<T>::operator==(const imatrix_t<T>& other) const {
    if (row_size_ == other.row_size_ && column_size_ == other.  column_size_) {
        for (int i = 0; i < row_size_ * column_size_; i++) {
            if (data_->data_()[i] != other.data_->data_()[i]) {
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
            if (data_->data_()[i] != other.data_->data_()[i]) {
                return 1;
            }
        }
        return 0;
    }

    return 1;
}


}
