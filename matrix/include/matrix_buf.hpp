#include <iostream>
#include <cassert>
#include <memory>

//-----------------------------------------------------------------------------------------

template<typename T>
class matrix_buf_t {
    protected:
        class data_impl_t;
        std::shared_ptr<data_impl_t> data_ = nullptr;

//-----------------------------------------------------------------------------------------

        class data_impl_t {
            private:
                int capacity_ = 0;
                T*  raw_data_ = nullptr;
            public:
                data_impl_t(int capacity) :
                    capacity_(capacity),
                    raw_data_((capacity != 0) ?
                    static_cast<T*>(::operator new(sizeof(T) * capacity)) : nullptr)
                {/*std::clog << "Constructor:  " << capacity << std::endl;*/};

                data_impl_t(const data_impl_t& rhs) = delete;
                data_impl_t& operator=(const data_impl_t& rhs) = delete;

                data_impl_t(data_impl_t&& rhs) noexcept : raw_data_(rhs.raw_data_),
                                                          capacity_(rhs.capacity_) {
                    rhs.raw_data_ = nullptr;
                    rhs.capacity_ = 0;
                }
                data_impl_t& operator=(data_impl_t&& rhs) noexcept {
                    if (this == &rhs)
                        return *this;

                    raw_data_ = rhs.raw_data_;
                    std::swap(raw_data_, rhs.raw_data_);
                    std::swap(capacity_, rhs.capacity_);

                    return *this;
                }
                ~data_impl_t() {
                    destroy();
                    ::operator delete(raw_data_);
                }
                void destroy() {
                    /*std::clog << "Destructor:" << this << "   " << capacity_ << std::endl;*/
                    for (int i = 0; i < capacity_; i++) {
                        raw_data_[i].~T();
                    }
                }
                int get_capacity() const {return capacity_;};
                T*  data_()              {return raw_data_;};
        };

//-----------------------------------------------------------------------------------------

        int get_capacity() const {
            if (data_) return data_->get_capacity();
            return 0;
        }
        matrix_buf_t() : data_(nullptr){};
        matrix_buf_t(int capacity) : data_(new data_impl_t(capacity)){};
};
