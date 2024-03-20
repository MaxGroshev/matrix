#pragma once
#include "matrix_oper.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix {

template <typename T>
class lazy_matrix_t : public imatrix_t<T> {
    private:
        using matrix_buf_t<T>::data_;
        using matrix_buf_t<T>::capacity_;
        bool sole_owner = true;
    public:
        using imatrix_t<T>::row_size_;
        using imatrix_t<T>::column_size_;
        void foo() {std::cout << data_  << row_size_ << this->transpose();};

//         lazy_matrix(const lazy_matrix<T>& other) :
//             data_(other->data_),
//             capacity_(other->capacity_) {
//
//         }
        lazy_matrix_t<T>& operator=(const lazy_matrix_t<T>& other);
//
//
//         };
};

template<typename T>
lazy_matrix_t<T>& lazy_matrix_t<T>::operator=(const lazy_matrix_t<T>& other) {
    matrix_buf_t<T>::mx_retain(other.data);
}

}
