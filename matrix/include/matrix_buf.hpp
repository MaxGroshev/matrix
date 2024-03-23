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
                int ref_cnt_  = 0;
                T*  raw_data_ = nullptr;
            public:
                data_impl_t(int capacity) :
                    capacity_(capacity),
                    ref_cnt_(1),
                    raw_data_((capacity != 0) ?
                    static_cast<T*>(::operator new(sizeof(T) * capacity)) : nullptr)
                {std::clog << "Constructor:  " << capacity << std::endl;};

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
                    std::swap(ref_cnt_, rhs.ref_cnt_);

                    return *this;
                }
                ~data_impl_t() {
                    // std::clog << "Destructor:" << this << "   " << capacity_ << std::endl;
                    ref_cnt_--;
                    destroy();
                    ::operator delete(raw_data_);
                }
                void destroy() {
                    for (int i = 0; i < capacity_; i++) {
                        raw_data_[i].~T();
                    }
                }
                int get_ref_cnt()  const {return ref_cnt_;};
                int get_capacity() const {return capacity_;};
                T*  data_()              {return raw_data_;};
                int release_mem_object() {return ref_cnt_--;}
                int retain_mem_object()  {return ref_cnt_++;}
        };

//-----------------------------------------------------------------------------------------

        int get_capacity() const {
            if (data_) return data_->get_capacity();
            return 0;
        }
        matrix_buf_t() : data_(nullptr){};
        matrix_buf_t(int capacity) : data_(new data_impl_t(capacity)){};
        matrix_buf_t(const matrix_buf_t<T>& rhs) {
            if (data_) {
                data_->retain_mem_object();
                std::clog << data_->ref_cnt_ << std::endl;
            }
        }
        matrix_buf_t(matrix_buf_t<T>&& rhs) noexcept {
            // std::clog << "Going to move\n" << std::endl;
            std::swap(data_, rhs.data_);
        };

        matrix_buf_t& operator=(const matrix_buf_t<T>& rhs) {
            if (data_) {
                data_->retain_mem_object();
                std::clog << data_->ref_cnt_ << std::endl;
            }
            return *this;
        }
        matrix_buf_t& operator=(matrix_buf_t<T>&& rhs) {
            if (this == &rhs)
                return *this;
            // std::clog << "Going to move from assign\n" << std::endl;
            std::swap(data_, rhs.data_);
            return *this;
        }

        // ~matrix_buf_t() {
        //     if (data_) {
        //         data_->~data_impl_t();
        //         ::operator delete(data_);
        //     }
        //     // else if (data_) {
        //     //     std::clog << "Releasing:" << this << std::endl;
        //     //     data_->release_mem_object();
        //     // }
        // }
};
