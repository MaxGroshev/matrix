#include <iostream>

//-----------------------------------------------------------------------------------------

template<typename T>
class matrix_buf_t {
    protected:
        T*  data_ = nullptr;
        int capacity_ = 0;


        matrix_buf_t(int capacity) :
            capacity_(capacity),
            data_(static_cast<T*>(::operator new(sizeof(T) * capacity)))
        {};
        matrix_buf_t(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t& operator=(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t(matrix_buf_t<T>&& rhs) noexcept : data_(rhs.data_),
                                                       capacity_(rhs.capacity_) {
            rhs.data_ = nullptr;
            rhs.capacity_ = 0;
        }
        matrix_buf_t& operator=(matrix_buf_t<T>&& rhs) {
            if (this = &rhs)
                return *this;

            std::swap(data_, rhs.data_);
            std::swap(capacity_, rhs.capacity_);

            return *this;
        }
        ~matrix_buf_t() {
            destroy();
            ::operator delete(data_);
        }

        void destroy() {
            for (int i = 0; i < capacity_; i++) {
                data_[i].~T();
            }
        }
};
