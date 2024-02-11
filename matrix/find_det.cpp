#include "ui.hpp"

//-----------------------------------------------------------------------------------------

using namespace matrix_ui;

int main() {

    double det =  run_find_of_det<double>();
    auto start_time = time_control::chrono_cur_time ();
    std::cout << det << '\n';
    auto end_time = time_control::chrono_cur_time ();
    time_control::show_run_time(start_time, end_time, "Time searching of det: ");

    return 0;
}
