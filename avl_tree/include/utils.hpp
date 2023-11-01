#include <iostream>
#include <cmath>
#include "debug_utils.hpp"

//-----------------------------------------------------------------------------------------

template <typename T>
T find_max (const T x, const T y) {
    if (x > y) return x;
    return y;
}

static bool in_interval(const size_t l_border, const size_t r_border, const size_t val) {
    if (val >= l_border && val <= r_border) return true;
    return false;
}

//-----------------------------------------------------------------------------------------
