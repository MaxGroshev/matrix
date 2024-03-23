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

        imatrix_t<T> raise_to_power(int power) const {
            if (power <= 1)
                return imatrix_t<T> {*this};

            const lazy_matrix_t<T>& m = *this;
            std::vector<lazy_matrix_t<T>> buf_of_mx {};
            buf_of_mx.push_back(m);

            buf_of_mx.push_back(m * m);
            lazy_matrix_t ret_matrix{m * m};

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

                    ret_matrix = ret_matrix * buf_of_mx[cnt - 1];
                    i += cnt;
                }
            }
            return ret_matrix;
        }
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
