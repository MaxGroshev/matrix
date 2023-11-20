#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <cassert>

//-----------------------------------------------------------------------------------------

namespace row {

template<typename T>
struct row_t final {
    public:
        T* data_;
        int size_;

    row_t(std::vector<T> data) : size_(data.size()), data_(new T[data.size()]) {
        for (int i = 0; i < data.size(); ++i) {
            data_[i] = data[i];
            std::cout << data_[i] << '\n';
        }
    };
    row_t(row_t<T>&& row) : size_(row.size_) {
        std::cout << "Move constr";
        if (this == &row)
            return;

        data_ = row.data_;
    };
    ~row_t() {
        delete [] data_;
        std::cout << "Row_destructor\n";
    };
    int operator[](const int pos) {
        if (pos < 0 || pos > size_) {
            std::cerr << "Elem is out of row";
        }
        return data_[pos];
    }
    // const T& operator[](const int pos) const {
    //     if (pos < 0 || pos > size_) {
    //         std::cerr << "Elem is out of row";
    //     }
    //     return data_[pos];
    // }
    // void print(std::ostream & out_strm = std::cout) const {
    //     for (const auto& elem : data_) {
    //         out_strm << "[" << elem << "]";
    //     }
    // };
};

//-----------------------------------------------------------------------------------------

template<typename T>
row_t<T> operator+(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.size_ != rhs.size_) {
        std::cerr << "Wrong oper on row";
    }

    std::vector<T> res;
    for (int i = 0; i < lhs.size_; i++) {
        res.push_back(lhs.data_[i] + rhs.data_[i]);
    }

    return row_t{res};
}

template<typename T>
row_t<T> operator-(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different sizes of row";

    std::vector<T> res;
    for (int i = 0; i < lhs.size_; i++) {
        res.push_back(lhs.data_[i] - rhs.data_[i]);
    }

    return row_t{res};
}

template<typename T>
T operator*(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.size_ != rhs.size_)
        throw "Different sizes of row";

    std::vector<T> res;
    T ij_elem = 0;
    for (int i = 0; i < lhs.size_; i++) {
        ij_elem += (lhs.data_[i] * rhs.data_[i]);
    }

    return ij_elem;
}

template<typename T>
row_t<T> operator*(const row_t<T>& lhs, const T val) {
    std::vector<T> res;
    for (int i = 0; i < lhs.size_; i++) {
        res.push_back(lhs.data_[i] * val);
    }

    return row_t{res};
}

template<typename T>
row_t<T> operator*(const T val, const row_t<T>& rhs) {
    std::vector<T> res;
    for (int i = 0; i < rhs.size_; i++) {
        res.push_back(rhs.data_[i] * val);
    }

    return row_t{res};
}

}
