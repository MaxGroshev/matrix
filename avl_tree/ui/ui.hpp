#pragma once

//-----------------------------------------------------------------------------------------

#include <vector>
#include "graphviz.h"
#include "debug_utils.hpp"
#include "avl_tree.hpp"

//-----------------------------------------------------------------------------------------

namespace avl_tree_ui {

std::vector<size_t> test_user_data(std::istream & in_strm = std::cin);

// std::vector<size_t> get_and_test_user_data(std::istream & in_strm = std::cin);
// std::vector<size_t> start_tests(size_t count_of_triangles, triangle_vect user_triangles);
// void print_triangles(triangle_vect triangles, size_t count_of_triangle);
};

