#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {
    using namespace matrix;
    chain_t<imatrix_t<int>> mx_chain = mul_get_user_data<int>();

    auto start_time = time_control::chrono_cur_time ();
    auto mul_chain  = mx_chain.mul();
    auto end_time   = time_control::chrono_cur_time ();
    time_control::show_run_time(start_time, end_time, "Optimal mul_time: ");

    start_time = time_control::chrono_cur_time ();
    auto naive_mul_chain = mx_chain.naive_mul();
    end_time   = time_control::chrono_cur_time ();
    time_control::show_run_time(start_time, end_time, "Naive mul time: ");


    std::clog << "(Optimal_mul_res == Naive_mul_res)";
    std::cout << (mul_chain == naive_mul_chain) << "\n";

    return 0;
}
