#include <iostream>
#include <cassert>

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
            {        std::clog << "I am creating buffer\n" << capacity_<< std::endl;};
            data_impl_t(const data_impl_t& rhs) = delete;
            data_impl_t& operator=(const data_impl_t& rhs) = delete;
            data_impl_t(data_impl_t&& rhs) noexcept : raw_data_(rhs.raw_data_),
                                                      capacity_(rhs.capacity_) {
                rhs.raw_data_ = nullptr;
                        std::clog << "I am here\n";

                rhs.capacity_ = 0;
            }
            data_impl_t& operator=(data_impl_t&& rhs) noexcept {
                if (this == &rhs)
                    return *this;

                std::clog << "Moving\n" << std::endl;
                raw_data_ = rhs.raw_data_;
                std::swap(raw_data_, rhs.raw_data_);
                std::swap(capacity_, rhs.capacity_);
                std::swap(ref_cnt_, rhs.ref_cnt_);
                // rhs.raw_data_   = nullptr;
                // std::clog << "Moving\n\n";

                return *this;
            }
            ~data_impl_t() {

                // std::clog << "I am cleaning: " << capacity_ << std::endl;
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
        matrix_buf_t(int capacity) : data_((capacity != 0) ? new data_impl_t(capacity) : nullptr){
            std::clog << capacity << std::endl;
        };
        matrix_buf_t(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t& operator=(const matrix_buf_t<T>& rhs) = delete;
        matrix_buf_t(matrix_buf_t<T>&& rhs) noexcept {
            std::clog << "Going to move\n" << std::endl;
            std::swap(data_, rhs.data_);
        };
        matrix_buf_t& operator=(matrix_buf_t<T>&& rhs) {
            if (this == &rhs)
                return *this;
            std::clog << "Going to move from assign\n" << std::endl;
            std::swap(data_, rhs.data_);
            return *this;
        }
        ~matrix_buf_t() {
            std::clog << "Destructor:" << this << std::endl;
            if (data_)
                data_->~data_impl_t();
            ::operator delete(data_);
        }
};