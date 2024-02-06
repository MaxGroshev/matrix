#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "debug_utils.hpp"
#include "time_control.hpp"
#include "matrix_oper.hpp"
#include "matrix.hpp"
#include "matrix_chain.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix_ui {

using namespace time_control;

template <typename T>
std::pair<std::vector<T>, int> det_get_user_data(std::istream & in_strm);

template <typename T>
std::pair<std::vector<T>, int> order_get_user_data(std::istream & in_strm);

template <typename T>
matrix::imatrix_t<T> get_matrix(int i, int j, std::istream & in_strm);

//-----------------------------------------------------------------------------------------

template <typename T>
std::vector<T> run_find_mul_order(std::istream & in_strm = std::cin) {
    auto user_data = order_get_user_data<T>(in_strm);

    matrix::chain_t<matrix::imatrix_t<int>> mx_chain {user_data.first};
    mx_chain.find_mul_order();
    return mx_chain.get_mul_order();
}

template <typename T>
std::pair<std::vector<T>, int> order_get_user_data(std::istream & in_strm) {
    int num_of_elems = 0;
    in_strm >> num_of_elems;

    int mx_size = 0;

    std::vector<int> data;
    for (int i = 0; i < num_of_elems; i++) { //^D to exit from cin input
        in_strm >> mx_size;
        data.push_back(mx_size);
    }
    std::pair<std::vector<int>, int> user_data(data, 0);
    return user_data;
}


//-----------------------------------------------------------------------------------------
template <typename T>
matrix::chain_t<matrix::imatrix_t<T>>get_mx_data(std::istream & in_strm = std::cin) {
    using namespace matrix;

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

    int elem = 0;
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
    auto user_data = det_get_user_data<T>(in_strm);

    matrix::sq_matrix_t<T> my_matrix(user_data.first, user_data.second);
    return my_matrix.find_det();
}

template <typename T>
std::pair<std::vector<T>, int> det_get_user_data(std::istream & in_strm) {
    assert(in_strm.good());

    T elem  = 0;
    std::vector<T> data;
    int matrix_size = 0;

    in_strm >> matrix_size;
    if (matrix_size < 0) {
        "Wrong input of data\n";
        exit(1);
    }

    for (int i = 0; i < matrix_size * matrix_size; i++) {
        if (in_strm.eof()) {
            "Wrong input of data\n";
            exit(1);
        }
        in_strm >> elem;
        data.push_back(elem);
    }

    std::pair<std::vector<T>, int> user_data(data, matrix_size);
    return user_data;
};

};

