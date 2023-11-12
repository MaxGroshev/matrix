#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {

    auto tree_start_time = time_control::chrono_cur_time ();
    long det =  run_find_of_det<long>();
    std::cout << det << '\n';
    auto tree_end_time = time_control::chrono_cur_time ();

    std::clog << "----------------------------------------------\n";
    std::clog << "Total run time: " << (tree_end_time - tree_start_time) / 0.1ms
    << " * 10^(-5) sec\n";


    return 0;
}
