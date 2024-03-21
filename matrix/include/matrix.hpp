#pragma once
#include <compare>
#include <iostream>
#include <cassert>
#include <vector>
#include "matrix_buf.hpp"
#include "matrix_execeptions.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template<typename T>
class imatrix_t : private matrix_buf_t<T> {
    private:
        class proxy_row_t;

    public:
        using matrix_buf_t<T>::data_;
        int row_size_   = 0; //num of elems in row
        int column_size_ = 0;

    imatrix_t() : matrix_buf_t<T>() {};

    imatrix_t(std::vector<T>& data, int column_size, int row_size) :
        row_size_(row_size), column_size_(column_size),
        matrix_buf_t<T>(row_size * column_size) {

        new (data_->data_()) T [row_size * column_size];
        for (int i = 0; i < row_size * column_size; i++) {
            data_->data_()[i] = data[i];
        }
    }

    imatrix_t(int column_size, int row_size) :
        row_size_(row_size),
        column_size_(column_size),
        matrix_buf_t<T>(row_size * column_size) {};

    imatrix_t(int column_size, int row_size, T val) :
        row_size_(row_size),
        column_size_(column_size),
        matrix_buf_t<T> (row_size * column_size) {
        for (int i = 0; i < column_size * row_size; i++) {
            data_->data_()[i] = val;
        }
        // std::fill(data_, row_size * column_size * sizeof(T) , val);
    };

    imatrix_t(const imatrix_t<T>& other) : row_size_(other.row_size_),
                                           column_size_(other.column_size_),
                                           matrix_buf_t<T>(other.get_capacity()) {

        new (data_->data_()) T [other.get_capacity()];
        std::clog << "I am copying matrix:" << &other << std::endl;
        for (int i = 0; i < other.get_capacity(); i++) {
            data_->data_()[i] = other.data_->data_()[i];
        }
    };
    imatrix_t(imatrix_t<T>&& other) = default;


    imatrix_t&        operator=(const imatrix_t<T>& other);
    imatrix_t&        operator=(imatrix_t<T>&& other) = default;
    proxy_row_t       operator[](const int pos);
    const proxy_row_t operator[](const int pos) const;
    int operator==(const imatrix_t<T>& other) const;
    int operator!=(const imatrix_t<T>& other) const;


    imatrix_t& transpose() &;
    imatrix_t  transpose() const &;
    imatrix_t& negate   () &;
    T          find_det () const;
    void       swap_rows(const int lhs, const int rhs);
    void       print(std::ostream & out_strm = std::cout) const;

//-----------------------------------------------------------------------------------------

    private:
        class proxy_row_t{
            public:
                T* row_;
                int size_ = 0;
                proxy_row_t (T* row, int size) : row_(row), size_(size) {};

                T& operator[](const int pos) {
                    if (pos < 0 || pos > size_)
                        throw("Elem is out of row");
                    return row_[pos];
                }
                const T& operator[](const int pos) const {
                    if (pos < 0 || pos > size_)
                        throw("Elem is out of row");
                    return row_[pos];
                }
        };
};

template<typename T>
class sq_matrix_t : public imatrix_t<T> {
    public:
        sq_matrix_t(std::vector<T>& data, int size) : imatrix_t<T> {data, size, size} {

        }
        sq_matrix_t(int size) : imatrix_t<T> {size, size} {};
};

//-----------------------------------------------------------------------------------------

template<typename T>
typename imatrix_t<T>::proxy_row_t imatrix_t<T>::operator[](const int pos) {
    if (pos < 0 || pos > column_size_) {
        std::cerr << "Elem is out of row";
        return (*this)[0];
    }
    proxy_row_t ret_row {data_->data_() + (pos * row_size_), row_size_};
    return ret_row;        //make func for rt of raw
}

template<typename T>
const typename imatrix_t<T>::proxy_row_t imatrix_t<T>::operator[](const int pos) const {
    if (pos < 0 || pos > column_size_) {
        std::cerr << "Elem is out of row";
        return (*this)[0];
    }
    proxy_row_t ret_row {data_->data_() + (pos * row_size_), row_size_};
    return ret_row;
}

//-----------------------------------------------------------------------------------------

template<typename T>
imatrix_t<T>& imatrix_t<T>::transpose() & {

    imatrix_t<T> tmp_m {row_size_, column_size_};
    imatrix_t<T>& m = *this;
    for (int i = 0; i < column_size_; i++) {
        for (int j = 0; j < row_size_; j++) {
            tmp_m[j][i] = m[i][j];
        }
    }
    std::swap(data_, tmp_m.data_);
    row_size_   = tmp_m.row_size_;
    column_size_= tmp_m.column_size_;
    return *this;
}

template<typename T>
imatrix_t<T> imatrix_t<T>::transpose() const & {
    const imatrix_t<T>& m = *this;
    imatrix_t ret_matrix{row_size_, column_size_};

    for (int i = 0; i < column_size_; i++) {
        for (int j = 0; j < row_size_; j++) {
            ret_matrix[j][i] = m[i][j];
        }
    }
    // ret_matrix.print();
    return ret_matrix;
}

template<typename T>
imatrix_t<T>& imatrix_t<T>::negate() & { //for square matrix
    const imatrix_t<T>& m = *this;
    for (int i = 0; i < column_size_; i++) {
        for (int j = 0; j < row_size_; j++) {
            m[i][j] *= -1;
        }
    }
    return *this;
}

template<typename T>
void imatrix_t<T>::swap_rows(const int lhs, const int rhs) {
    for (int i = 0; i < row_size_; i++) {
        T tmp = data_->data_()[i + lhs * row_size_];
        data_->data_()[i + lhs * row_size_] = data_->data_()[i + rhs * row_size_];
        data_->data_()[i + rhs * row_size_] = tmp;
    }
}

//-----------------------------------------------------------------------------------------

template<typename T>
T imatrix_t<T>::find_det() const { //Barreis algorithm
    if (column_size_ != row_size_)
        throw ("Incorrect size of matrix for determinant");
    if (row_size_ == 0) return 0;

    int det_sign = 1;
    imatrix_t<T> matrix(*this);
    for (int i = 0; i < matrix.row_size_; i++) {
        if (matrix[i][i] == 0) {
            int j = 0;
            for (j = i + 1; j < matrix.row_size_; j++) {
                if (matrix[j][i] != 0) {
                    matrix.swap_rows(i, j);
                    det_sign *= -1;
                    break;
                }
            }
            if (j == matrix.row_size_) {
                return 0;
            }
        }

        for (int k = i + 1; k < matrix.row_size_; k++) {
            for (int m = i + 1; m < matrix.row_size_; m++) {
                matrix[k][m] = matrix[k][m] * matrix[i][i] -
                               matrix[k][i] * matrix[i][m];
                if (i != 0) {
                    matrix[k][m] /= matrix[i - 1][i - 1];
                }
            }
        }
    }

    return det_sign * matrix[matrix.row_size_ - 1][matrix.row_size_ - 1];
}

//-----------------------------------------------------------------------------------------

template <typename T>
void imatrix_t<T>::print(std::ostream & out_strm) const {

    out_strm << "------------------------------\n";
    out_strm << "Print of matrix:\n";
    out_strm << "Column_size: " << column_size_ << '\n';
    out_strm << "Row_size:    " << row_size_;

    for (int i = 0; i < column_size_ * row_size_; i++) {
        if (i % row_size_ == 0)
            std::cout << '\n';
        std::cout << "[" << data_->data_()[i] << "] ";
    }
    out_strm << "\n------------------------------";
    std::cout << '\n';
}

}
