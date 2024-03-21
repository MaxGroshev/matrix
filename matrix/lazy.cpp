#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {
    std::vector<int> v = {1, 2, 3, 4};
    matrix::lazy_matrix_t<int> mx{v, 3, 3};

    return 0;
}
