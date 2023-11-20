#pragma once
// #include "rows.hpp"
#include <iostream>
#include <cassert>
#include <vector>

//-----------------------------------------------------------------------------------------

namespace matrix {

// using namespace row;

template<typename T>
class sq_matrix_t final {
    private:
        class proxy_row_t;
    public:
        T* data_;
        int size_;


    sq_matrix_t(std::vector<T>& data, size_t size) : size_(size) {
        data_ = new T [size * size];
        for (int i = 0; i < size * size; i++) {
            data_[i] = data[i];
            // std::cout << data_[0].row_->data_[0];
        }
    }
    sq_matrix_t(size_t size) : size_(size), data_(new T [size * size]) {}
    // sq_matrix_t(std::vector<std::unique_ptr<row_t<T>>>& data, size_t size) : size_(size) {
    //     for (int i = 0; i < size; i++) {
    //         data_.push_back(row_t{std::move(data_[i])});
    //     }
    // }
    sq_matrix_t(const sq_matrix_t<T>& other) : size_(other.size_) {
        data_ = new T [size_ * size_];
        for (int i = 0; i < size_ * size_; i++) {
            // std::vector<T> row_data;
            data_[i] = other.data_[i];
        }
    }
    // sq_matrix_t(sq_matrix_t<T>&& other) noexcept : size_(other.size_) {
    //     for (int i = 0; i < other.data_.size(); i++) {
    //         data_.push_back(std::move(other.data_[i]));
    //     }
    // }
    ~sq_matrix_t() {
        // std::cout << "Hey\n\n\n\n";
        delete [] data_;
    }


    sq_matrix_t operator=(const sq_matrix_t<T>& other) {
    };
    sq_matrix_t operator=(sq_matrix_t<T>&& other) noexcept;
    proxy_row_t operator[](const int pos) {
        if (pos < 0 || pos > size_) {
            std::cerr << "Elem is out of row";
            // return data_[0];
        }
        proxy_row_t ret_row {data_ + (pos * size_), size_};
        return ret_row;
    };
    const proxy_row_t operator[](const int pos) const {
        if (pos < 0 || pos > size_) {
            std::cerr << "Elem is out of row";
            // return data_[0];
        }
        proxy_row_t ret_row {data_ + (pos * size_), size_};
        return ret_row;
    };

    sq_matrix_t& transpose() &;
    sq_matrix_t  transpose() const &;
    sq_matrix_t& negate   () &;
    T find_det() const;
    void swap_rows(const int lhs, const int rhs) {
        for (int i = 0; i < size_; i++) {
            T tmp = data_[i + lhs * size_];
            data_[i + lhs * size_] = data_[i + rhs * size_];
            data_[i + rhs * size_] = tmp;
        }
    }
    void print(std::ostream & out_strm = std::cout) const;


    private:
        class proxy_row_t{
            public:
                T* row_;
                int size_ = 0;
                proxy_row_t (T* row, int size) : row_(row), size_(size) {};

                T& operator[](const int pos) {
                    if (pos < 0 || pos > size_) {
                        std::cerr << "Elem is out of row";
                    }
                    return row_[pos];
                }
                const T& operator[](const int pos) const {
                    if (pos < 0 || pos > size_) {
                        std::cerr << "Elem is out of row";
                    }
                    return row_[pos];
                }
        };
};

//-----------------------------------------------------------------------------------------

// template<typename T>
// typename row_t<T>::row_t<T>& sq_matrix_t<T>::operator[](const int pos) {
//     if (pos < 0 || pos > data_.size()) {
//         std::cerr << "Elem is out of row";
//         return data_[0];
//     }
//     return data_[pos];
// }

// template<typename T>
// const typename row_t<T>& sq_matrix_t<T>::operator[](const int pos) const {
//     if (pos < 0 || pos > data_.size()) {
//         std::cerr << "Elem is out of row";
//         return data_[0];
//     }
//     return data_[pos];
// }

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T>& sq_matrix_t<T>::transpose() & {
    sq_matrix_t<T>& m = *this;
    // std::cout << "Transposing\n";
    for (int i = 0; i < size_; i++) {
        for (int j = i; j < size_; j++) {
            T tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
    return *this;
}

template<typename T>
sq_matrix_t<T> sq_matrix_t<T>::transpose() const & {
    sq_matrix_t ret_matrix{size_};
    for (int i = 0; i < ret_matrix.size_ * ret_matrix.size_; i++) {
        ret_matrix.data_[i] = data_[i];
    }
    return ret_matrix;
}

template<typename T>
sq_matrix_t<T>& sq_matrix_t<T>::negate() & { //for square matrix
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            data_[i][j] *= -1;
        }
    }
    return *this;
}

//-----------------------------------------------------------------------------------------

template<typename T>
T sq_matrix_t<T>::find_det() const { //Barreis algorithm
    if (size_ == 0) return 0;

    int det_sign = 1;
    sq_matrix_t<T> matrix(*this);
    // matrix.transpose();
    for (int i = 0; i < matrix.size_; i++) {
        if (matrix[i][i] == 0) {
            int j = 0;
            for (j = i + 1; j < matrix.size_; j++) {
                if (matrix[j][i] != 0) {
                    matrix.swap_rows(i, j);
                    // std::cout << "Geree\n";
                    det_sign *= -1;
                    break;
                }
            }
            if (j == matrix.size_) {
                return 0;
            }
        }

        for (int k = i + 1; k < matrix.size_; k++) {
            for (int m = i + 1; m < matrix.size_; m++) {
                matrix[k][m] = matrix[k][m] * matrix[i][i] -
                                     matrix[k][i] * matrix[i][m];
                if (i != 0) {
                    matrix[k][m] /= matrix[i - 1][i - 1];
                }
            }
        }
        // std::cout << "-------------------------------------";
        // std::cout << "DET: " << matrix.data_[matrix.size_ - 1][matrix.size_ - 1] << '\n';
    }

    return det_sign * matrix[matrix.size_ - 1][matrix.size_ - 1];
}

//-----------------------------------------------------------------------------------------

template <typename T>
void sq_matrix_t<T>::print(std::ostream & out_strm) const {

    out_strm << "Print of matrix:\n";
    for (int i = 0; i < size_ * size_; i++) {
        if (i % size_ == 0)
            std::cout << '\n';
        std::cout << "[" << data_[i] << "] ";
    }
    std::cout << '\n';
}

}
