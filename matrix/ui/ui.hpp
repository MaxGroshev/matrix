#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "debug_utils.hpp"
#include "time_control.hpp"
#include "matrix_oper.hpp"
#include "matrix.hpp"

//-----------------------------------------------------------------------------------------

namespace matrix_ui {

using namespace time_control;

template <typename T>
std::pair<std::vector<T>, int> get_user_data(std::istream & in_strm);

template <typename T>
T run_find_of_det(std::istream & in_strm = std::cin) {
    auto user_data = get_user_data<T>(in_strm);

    matrix::sq_matrix_t<T> my_matrix(user_data.first, user_data.second);
    return my_matrix.find_det();
}

template <typename T>
std::pair<std::vector<T>, int> get_user_data(std::istream & in_strm) {
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
        // std::cout << elem << '\n';
        data.push_back(elem);
    }

    std::pair<std::vector<T>, int> user_data(data, matrix_size);
    return user_data;
};

};

