#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "debug_utils.hpp"
#include "time_control.hpp"
#include "matrix_oper.hpp"
#include "matrix_chain.hpp"
#include "matrix_chain.hpp"
#include "lazy_matrix.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix_ui {

using namespace time_control;

template <typename T>
std::vector<T> order_get_user_data(std::istream & in_strm);

template <typename T>
matrix::imatrix_t<T> get_matrix(int i, int j, std::istream & in_strm);

//-----------------------------------------------------------------------------------------

template <typename T>
std::vector<T> run_find_mul_order(std::istream & in_strm = std::cin) {
    auto user_data = order_get_user_data<T>(in_strm);

    matrix::chain_t<matrix::imatrix_t<int>> mx_chain {user_data};
    mx_chain.find_mul_order();
    return mx_chain.get_mul_order();
}

template <typename T>
std::vector<T> order_get_user_data(std::istream & in_strm) {
    in_strm.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int num_of_elems = 0;
    in_strm >> num_of_elems;

    int mx_size = 0;

    std::vector<int> data;
    for (int i = 0; i < num_of_elems; i++) { //^D to exit from cin input
        in_strm >> mx_size;
        data.push_back(mx_size);
    }
    return data;
}

//-----------------------------------------------------------------------------------------

template <typename T>
std::pair<matrix::imatrix_t<T>, int>power_get_user_data(std::istream & in_strm = std::cin) {
    using namespace matrix;
    in_strm.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int power = 0;
    int n_col = 0;
    int n_row = 0;
    in_strm >> power >> n_col >> n_row;

    imatrix_t<T> mx = get_matrix<T>(n_col, n_row, in_strm);

    return std::pair {std::move(mx), power};
}

//-----------------------------------------------------------------------------------------

template <typename T>
matrix::chain_t<matrix::imatrix_t<T>>mul_get_user_data(std::istream & in_strm = std::cin) {
    using namespace matrix;
    in_strm.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    chain_t<imatrix_t<int>> mx_chain;
    int count_of_mx = 0;
    in_strm >> count_of_mx;
    int count_of_mx_sizes = count_of_mx + 1;

    std::vector<int> mx_sizes;
    int mx_size = 0;
    for (int i = 0; i < count_of_mx_sizes; ++i) {
        in_strm >> mx_size;
        mx_sizes.push_back(mx_size);
    }

    for (int i = 0; i < count_of_mx; ++i) {
        imatrix_t<T> mx = get_matrix<T>(mx_sizes[i], mx_sizes[i + 1], in_strm);
        mx_chain.push_back(mx);
    }

    return mx_chain;
}

template <typename T>
matrix::imatrix_t<T> get_matrix(int i, int j, std::istream & in_strm) {

    T elem = 0;
    std::vector<T> elems;
    for (int k = 0; k < i * j; k++) {
        in_strm >> elem;
        elems.push_back(elem);
    }
    return matrix::imatrix_t<T> {elems, i, j};
}

//-----------------------------------------------------------------------------------------

template <typename T>
T run_find_of_det(std::istream & in_strm = std::cin) {
    in_strm.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    int mx_size = {};
    try {
        in_strm >> mx_size;
        auto my_matrix = get_matrix<T>(mx_size, mx_size, in_strm);
        return my_matrix.find_det();
    } catch (std::ifstream::failure error) {
        std::cerr << "Error of input: " << error.what() << std::endl;
    } catch (...) {
        throw;
    }
    return -1;
}
};
