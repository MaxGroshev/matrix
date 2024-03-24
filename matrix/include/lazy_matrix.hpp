#pragma once
#include "matrix_oper.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template <typename T>
class lazy_matrix_t : public imatrix_t<T> {
    public:
        using matrix_buf_t<T>::data_;
        using imatrix_t<T>::row_size_;
        using imatrix_t<T>::column_size_;
        lazy_matrix_t(std::vector<T>& data, int column_size, int row_size) :
            imatrix_t<T>(data, column_size, row_size) {};
        lazy_matrix_t(int column_size, int row_size, T val) :
            imatrix_t<T>(column_size, row_size, val) {};
        lazy_matrix_t(int column_size, int row_size) :
            imatrix_t<T>(column_size, row_size) {};

        lazy_matrix_t(const lazy_matrix_t<T>& other) : imatrix_t<T>() {
            row_size_ = other.row_size_;
            column_size_ = other.column_size_;
            this->data_ = other.data_;
        }
        lazy_matrix_t(const imatrix_t<T>& other) : imatrix_t<T>() {
            row_size_ = other.row_size_;
            column_size_ = other.column_size_;
            this->data_ = other.data_;
        }

        lazy_matrix_t(lazy_matrix_t<T>&& other) = default;
        lazy_matrix_t<T>& operator=(const lazy_matrix_t<T>& other);
        lazy_matrix_t<T>& operator=(const imatrix_t<T>& other);

        ~lazy_matrix_t() = default;
};

template<typename T>
lazy_matrix_t<T>& lazy_matrix_t<T>::operator=(const lazy_matrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    imatrix_t<T> tmp_matrix {};
    std::swap(data_, tmp_matrix.data_);
    row_size_ = other.row_size_;
    column_size_ = other.column_size_;
    this->data_ = other.data_;

    return *this;
}

template<typename T>
lazy_matrix_t<T>& lazy_matrix_t<T>::operator=(const imatrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    imatrix_t<T> tmp_matrix {};
    std::swap(data_, tmp_matrix.data_);
    row_size_ = other.row_size_;
    column_size_ = other.column_size_;
    this->data_ = other.data_;

    return *this;
}
}

//-----------------------------------------------------------------------------------------
