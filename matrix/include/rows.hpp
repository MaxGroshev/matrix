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
        std::vector<T> data_;


    row_t(std::vector<T> data) : data_(data) {};
    void print(std::ostream & out_strm = std::cout) const {
        for (const auto& elem : data_) {
            out_strm << "[" << elem << "]";
        }
    };
};

//-----------------------------------------------------------------------------------------

template<typename T>
row_t<T> operator+(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.data_.size() != rhs.data_.size()) {
        std::cerr << "Wrong oper on row";
    }

    std::vector<T> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        res.push_back(lhs.data_[i] + rhs.data_[i]);
    }

    return row_t{res};
}

template<typename T>
row_t<T> operator-(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.data_.size() != rhs.data_.size())
        throw "Different sizes of row";

    std::vector<T> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        res.push_back(lhs.data_[i] - rhs.data_[i]);
    }

    return row_t{res};
}

template<typename T>
T operator*(const row_t<T>& lhs, const row_t<T>& rhs) {
    if (lhs.data_.size() != rhs.data_.size())
        throw "Different sizes of row";

    std::vector<T> res;
    T ij_elem = 0;
    for (int i = 0; i < lhs.data_.size(); i++) {
        ij_elem += (lhs.data_[i] * rhs.data_[i]);
    }

    return ij_elem;
}

template<typename T>
row_t<T> operator*(const row_t<T>& lhs, const T val) {
    std::vector<T> res;
    for (int i = 0; i < lhs.data_.size(); i++) {
        res.push_back(lhs.data_[i] * val);
    }

    return row_t{res};
}

template<typename T>
row_t<T> operator*(const T val, const row_t<T>& rhs) {
    std::vector<T> res;
    for (int i = 0; i < rhs.data_.size(); i++) {
        res.push_back(rhs.data_[i] * val);
    }

    return row_t{res};
}

}
