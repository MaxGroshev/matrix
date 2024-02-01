#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {


    auto start_time = time_control::chrono_cur_time ();
    auto mul_order = run_find_mul_order<int>();
    auto end_time = time_control::chrono_cur_time ();

    std::clog << "----------------------------------------------\n";
    std::clog << "Total run time: " << (end_time - start_time) / 0.1ms
    << " * 10^(-5) sec\n";
    std::clog << "----------------------------------------------\n";

    for (int i = mul_order.size() - 1; i > -1; i--)
        std::cout << mul_order[i] << ' ';
    std::cout << std::endl;

    return 0;
}
