#pragma once
#include "rows.hpp"
#include <iostream>
#include <vector>

//-----------------------------------------------------------------------------------------

namespace matrix {

using namespace row;

template<typename T>
class sq_matrix_t final {
    private:
        class proxy_row_t {
            public:
                std::unique_ptr<row_t<T>> row_;

                proxy_row_t(std::vector<T>& data) {
                    row_ = {std::make_unique<row_t<T>>(row_t(data))};
                }
                proxy_row_t(std::unique_ptr<row_t<T>>&& row) : row_(std::move(row)){};
                T& operator[](const int pos) {
                    if (pos < 0 || pos > row_->data_.size()) {
                        std::cerr << "Elem is out of row";
                    }
                    return row_->data_[pos];
                }
                const T& operator[](const int pos) const {
                    if (pos < 0 || pos > row_->data_.size()) {
                        std::cerr << "Elem is out of row";
                    }
                    return row_->data_[pos];
                }
        };

    public:
        std::vector<proxy_row_t> data_;
        size_t size_;


    sq_matrix_t(std::vector<T>& data, size_t size) : size_(size) {
        for (int i = 0; i < size; i++) {
            std::vector<T> row_data;
            for (int j = i * size, k = 0; k < size; k++) {
                row_data.push_back(data[j + k]);
            }
            data_.push_back(proxy_row_t(row_data));
        }
    }
    sq_matrix_t(std::vector<std::unique_ptr<row_t<T>>>& data, size_t size) : size_(size) {
        for (int i = 0; i < size; i++) {
            data_.push_back(proxy_row_t{std::move(data[i])});
        }
    }
    sq_matrix_t(const sq_matrix_t<T>& other) : size_(other.size_) {
        for (int i = 0; i < other.size_; i++) {
            std::vector<T> row_data;
            for (int j = 0; j < other.size_; j++) {
                row_data.push_back(other.data_[i][j]);
            }
            data_.push_back(proxy_row_t(row_data));
        }
    }
    sq_matrix_t(sq_matrix_t<T>&& other) noexcept : size_(other.size_) {
        for (int i = 0; i < other.data_.size(); i++) {
            data_.push_back(std::move(other.data_[i]));
        }
    }
    ~sq_matrix_t() = default;


    inline sq_matrix_t        operator=(const sq_matrix_t<T>& other);
    inline sq_matrix_t        operator=(sq_matrix_t<T>&& other) noexcept;
    inline proxy_row_t&       operator[](const int pos);
    inline const proxy_row_t& operator[](const int pos) const;

    inline sq_matrix_t& transpose() &;
    inline sq_matrix_t  transpose() const &;
    inline sq_matrix_t& negate   () &;
    inline T find_det() const;
    inline void print(std::ostream & out_strm = std::cout) const;
};

//-----------------------------------------------------------------------------------------

template<typename T>
typename sq_matrix_t<T>::proxy_row_t& sq_matrix_t<T>::operator[](const int pos) {
    if (pos < 0 || pos > data_.size()) {
        std::cerr << "Elem is out of row";
        return data_[0];
    }
    return data_[pos];
}

template<typename T>
const typename sq_matrix_t<T>::proxy_row_t& sq_matrix_t<T>::operator[](const int pos) const {
    if (pos < 0 || pos > data_.size()) {
        std::cerr << "Elem is out of row";
        return data_[0];
    }
    return data_[pos];
}

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T>& sq_matrix_t<T>::transpose() & {
    for (int i = 0; i < size_; i++) {
        for (int j = i; j < size_; j++) {
            T tmp = data_[i][j];
            data_[i][j] = data_[j][i];
            data_[j][i] = tmp;
        }
    }
    return *this;
}

template<typename T>
sq_matrix_t<T> sq_matrix_t<T>::transpose() const & {
    std::vector<T> data;
    for (int i = 0; i < size_; i++) {
        for (int j = 0; j < size_; j++) {
            data.push_back(data_[j][i]);
        }
    }
    return sq_matrix_t{data, size_};
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

    for (int i = 0; i < matrix.size_; i++) {
        if (matrix.data_[i][i] == 0) {
            int j = 0;
            for (j = i + 1; j < matrix.size_; j++) {
                if (matrix.data_[j][i] != 0) {
                    std::swap(matrix.data_[i], matrix.data_[j]);
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
                matrix.data_[k][m] = matrix.data_[k][m] * matrix.data_[i][i] -
                                     matrix.data_[k][i] * matrix.data_[i][m];
                if (i != 0) {
                    matrix.data_[k][m] /= matrix.data_[i - 1][i - 1];
                }
            }
        }
        // std::cout << "-------------------------------------";
        // std::cout << "DET: " << matrix.data_[matrix.size_ - 1][matrix.size_ - 1] << '\n';
    }

    return det_sign * matrix.data_[matrix.size_ - 1][matrix.size_ - 1];
}

//-----------------------------------------------------------------------------------------

template <typename T>
void sq_matrix_t<T>::print(std::ostream & out_strm) const {

    out_strm << "Print of matrix:\n";
    for (const auto& proxy_row : data_) {
        out_strm << "[";
        proxy_row.row_->print();
        out_strm << "]\n";
    }
}

}
