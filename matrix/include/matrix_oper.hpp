#pragma once
#include "matrix.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template<typename T>
sq_matrix_t<T> operator+(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    std::vector<std::unique_ptr<row_t<T>>> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        std::unique_ptr sum_row = std::make_unique<row_t<T>>
                                                    (*(lhs[i].row_) + *(rhs[i].row_));
        res.push_back(std::move(sum_row));
    }
    return sq_matrix_t{res, lhs.size_};
}

template<typename T>
sq_matrix_t<T> operator-(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    std::vector<std::unique_ptr<row_t<T>>> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        std::unique_ptr sub_row = std::make_unique<row_t<T>>
                                                    (*(lhs[i].row_) - *(rhs[i].row_));
        res.push_back(std::move(sub_row));
    }
    return sq_matrix_t{res, lhs.size_};
}

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T> operator*(const sq_matrix_t<T>& lhs, const sq_matrix_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different size of matrixes\n";

    sq_matrix_t<T> rhs_transpose = rhs.transpose();
    std::vector<std::unique_ptr<row_t<T>>> res_matrix;
    for (int i = 0; i < rhs_transpose.data_.size(); i++) {
        std::vector<T> row_data;
        for (int j = 0; j < lhs.data_.size(); j++) {
            row_data.push_back((*(lhs[i].row_)) * (*(rhs_transpose[j].row_)));
        }
        std::unique_ptr mul_row = std::make_unique<row_t<T>>(row_t(row_data));
        res_matrix.push_back(std::move(mul_row));
    }
    return sq_matrix_t{res_matrix, lhs.size_};
}

template<typename T>
sq_matrix_t<T> operator*(const sq_matrix_t<T>& lhs, const T val) {

    std::vector<std::unique_ptr<row_t<T>>> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        std::unique_ptr sub_row = std::make_unique<row_t<T>>
                                                    (*(lhs[i].row_) * val);
        res.push_back(std::move(sub_row));
    }
    return sq_matrix_t{res, lhs.size_};
}

template<typename T>
sq_matrix_t<T> operator*(const T val, const sq_matrix_t<T>& rhs) {

    std::vector<std::unique_ptr<row_t<T>>> res;
    for (int i = 0; i < rhs.data_.size(); i++) {
        std::unique_ptr sub_row = std::make_unique<row_t<T>>
                                                    (val * (*(rhs[i].row_)));
        res.push_back(std::move(sub_row));
    }
    return sq_matrix_t{res, rhs.size_};
}

//-----------------------------------------------------------------------------------------

template<typename T>
sq_matrix_t<T> sq_matrix_t<T>::operator=(const sq_matrix_t<T>& other) {
    if (this == &other) {
        return *this;
    }

    return sq_matrix_t<T>(other);
}

template<typename T>
sq_matrix_t<T> sq_matrix_t<T>::operator=(sq_matrix_t<T>&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    return sq_matrix_t<T>(other);
}
}
