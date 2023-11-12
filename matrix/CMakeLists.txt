cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(matrix)

#-----------------------------------------------------------------------------------------

set(SOURCE
    ./main.cpp)

#-----------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SOURCE} ${DEBUG_UTILS})
target_link_libraries(${PROJECT_NAME} debug_utils)

target_include_directories(${PROJECT_NAME} PRIVATE ./ui
                                                   ./include/)



