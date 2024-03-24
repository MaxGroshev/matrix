#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {
    using namespace matrix;
    std::pair<matrix::imatrix_t<long>, int> data = power_get_user_data<long>();

    auto start_time = time_control::chrono_cur_time ();
    auto common_res_mx = matrix::raise_to_power(data.first, data.second);
    auto end_time   = time_control::chrono_cur_time ();
    time_control::show_run_time(start_time, end_time, "Common matrix mul time: ");

    matrix::lazy_matrix_t<long> lazy_mx {data.first};
    start_time = time_control::chrono_cur_time ();
    auto lazy_res_mx  = matrix::raise_to_power(lazy_mx, data.second);
    end_time   = time_control::chrono_cur_time ();
    time_control::show_run_time(start_time, end_time, "Lazy matrix mul time: ");
    // lazy_res_mx.print();


    std::cout << (common_res_mx == lazy_res_mx) << "\n";

    return 0;
}
