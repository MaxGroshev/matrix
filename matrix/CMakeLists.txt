cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(matrix)

#-----------------------------------------------------------------------------------------

set(ORDER
    ./main.cpp)

set(MX_MUL
    ./compare_mul.cpp)

#-----------------------------------------------------------------------------------------


add_executable(mx_order ${ORDER} ${DEBUG_UTILS})
add_executable(mx_mul ${MX_MUL} ${DEBUG_UTILS})
target_link_libraries(mx_order debug_utils)
target_link_libraries(mx_mul debug_utils)

target_include_directories(mx_order PRIVATE ./ui ./include/)
target_include_directories(mx_mul PRIVATE ./ui ./include/)



