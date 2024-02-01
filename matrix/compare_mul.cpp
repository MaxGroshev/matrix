#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {
    using namespace matrix;
    chain_t<imatrix_t<int>> mx_chain = get_mx_data<int>();

    auto start_time = time_control::chrono_cur_time ();
    auto mul_chain = mx_chain.mul();
    auto end_time   = time_control::chrono_cur_time ();
    std::clog << "----------------------------------------------\n";
    std::clog << "Total opt_mul time: " << (end_time - start_time) / 0.1ms
    << " * 10^(-5) sec\n";
    std::clog << "----------------------------------------------\n";


    start_time = time_control::chrono_cur_time ();
    auto naive_mul_chain = mx_chain.naive_mul();
    end_time   = time_control::chrono_cur_time ();
    std::clog << "----------------------------------------------\n";
    std::clog << "Total naive_mul time: " << (end_time - start_time) / 0.1ms
    << " * 10^(-5) sec\n";
    std::clog << "----------------------------------------------\n";

    std::clog << "(Optimal_mul_res == Naive_mul_res) == ";
    std::cout << (mul_chain == naive_mul_chain) << "\n";



    return 0;
}
