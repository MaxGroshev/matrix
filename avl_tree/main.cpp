#include "ui.hpp"

//-----------------------------------------------------------------------------------------


int main() {
    using namespace avl_tree_ui;

    // auto tree_start_time = time_control::chrono_cur_time ();
    avl_tree_ui::run_tree();
    // avl_tree_ui::run_set(std::cin);
    // pine.graphviz_dump();
    // auto tree_end_time = time_control::chrono_cur_time ();
    // std::cerr << "Total run time: " << (tree_end_time - tree_start_time) / 0.1ms  << '\n';

    return 0;
}
