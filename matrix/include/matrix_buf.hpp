#include <iostream>

//-----------------------------------------------------------------------------------------

template<typename T>
class matrix_buf_t {
    protected:
        struct data_impl_t;
        data_impl_t* data_ = nullptr; //make unique_ptr

        struct data_impl_t {
            int capacity_  = 0;
            int ref_cnt_   = 0;
            T*  raw_data_ = nullptr;
            data_impl_t(int capacity) :
                capacity_(capacity),
                ref_cnt_(1),
                raw_data_((capacity != 0) ?
                            static_cast<T*>(::operator new(sizeof(T) * capacity)) : nullptr)
            {};
            data_impl_t(const data_impl_t& rhs) = delete;
            data_impl_t& operator=(const data_impl_t& rhs) = delete;
            data_impl_t(data_impl_t&& rhs) noexcept : raw_data_(rhs.raw_data_),
                                                      capacity_(rhs.capacity_) {
                rhs.raw_data_ = nullptr;
                        // std::cout << "I am here\n";

                rhs.capacity_ = 0;
            }
            data_impl_t& operator=(data_impl_t&& rhs) {
                if (this == &rhs)
                    return *this;

                std::swap(raw_data_, rhs.raw_data_);
                std::swap(capacity_, rhs.capacity_);
                std::swap(ref_cnt_, rhs.ref_cnt_);
                // rhs.raw_data_   = nullptr;
                // std::cout << "Moving\n\n";

                return *this;
            }
            ~data_impl_t() {

                // std::cout << "I am cleaning: " << capacity_ << std::endl;
                destroy();
                ::operator delete(raw_data_);
            }

            void destroy() {
                for (int i = 0; i < capacity_; i++) {
                    raw_data_[i].~T();
                }
            }
        };

        int get_capacity() const {
            if (data_) return data_->capacity_;
            return 0;
        }
        matrix_buf_t(int capacity) : data_(new data_impl_t(capacity)){};
        matrix_buf_t(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t& operator=(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t(matrix_buf_t<T>&& rhs) noexcept : data_(std::move(rhs.data_)){
            rhs.data_ = nullptr;
        };
        matrix_buf_t& operator=(matrix_buf_t<T>&& rhs) {
            if (this == &rhs)
                return *this;
            std::cout << "Going to move\n" << std::endl;
            data_ = std::move(rhs.data_);
            rhs.data_ = nullptr;
            return *this;
        }
        ~matrix_buf_t() {
            if (data_)
                data_->~data_impl_t();
            ::operator delete(data_);
        }
};
