cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(matrix)

#-----------------------------------------------------------------------------------------

set(MX_ORDER
    ./mul_order.cpp)

set(MX_MUL
    ./compare_mul.cpp)

set(MX_DET
    ./find_det.cpp)

set (MX_LAZY
    ./lazy.cpp)

#-----------------------------------------------------------------------------------------


add_executable(mx_order ${MX_ORDER} ${DEBUG_UTILS})
add_executable(mx_mul   ${MX_MUL} ${DEBUG_UTILS})
add_executable(mx_det   ${MX_DET} ${DEBUG_UTILS})
add_executable(mx_lazy  ${MX_LAZY} ${DEBUG_UTILS})


target_link_libraries(mx_order debug_utils)
target_link_libraries(mx_mul   debug_utils)
target_link_libraries(mx_det   debug_utils)
target_link_libraries(mx_lazy  debug_utils)

target_include_directories(mx_order PRIVATE ./ui ./include/)
target_include_directories(mx_mul   PRIVATE ./ui ./include/)
target_include_directories(mx_det   PRIVATE ./ui ./include/)
target_include_directories(mx_lazy  PRIVATE ./ui ./include/)



