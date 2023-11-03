#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include <set>
#include "graphviz.h"
#include "debug_utils.hpp"
#include "time_control.hpp"
#include "avl_tree.hpp"

//-----------------------------------------------------------------------------------------

namespace avl_tree_ui {

using namespace time_control;

std::vector<size_t> test_user_data(std::istream & in_strm = std::cin);

template<typename T, typename key_type>
static size_t range_query(const T& container, key_type l_bound, key_type u_bound) {
    using iter = typename T::iterator;

    // auto start_time = chrono_cur_time ();
    iter start = container.lower_bound(l_bound);
    iter end   = container.upper_bound(u_bound);
    size_t res = std::distance(start, end); // make func param

    // auto end_time = chrono_cur_time ();
    // std::cerr << "Run time: " <<(end_time - start_time) / 0.1ms  << '\n';

    std::cout << res << '\n';
    return res;
}

};

