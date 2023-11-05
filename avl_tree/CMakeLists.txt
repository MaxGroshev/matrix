cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(avl_tree)

#-----------------------------------------------------------------------------------------

set(SOURCE
    ./main.cpp
    ./ui/ui.cpp)

#-----------------------------------------------------------------------------------------

add_executable(${PROJECT_NAME} ${SOURCE} ${DEBUG_UTILS})
target_link_libraries(${PROJECT_NAME} graphviz debug_utils)

target_include_directories(${PROJECT_NAME} PRIVATE ./ui
                                                    ./include/)



