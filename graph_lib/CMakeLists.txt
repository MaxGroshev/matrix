cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(graphviz)

#-----------------------------------------------------------------------------------------

set(SOURCE
    ./func.cpp
    )

#-----------------------------------------------------------------------------------------

add_library(${PROJECT_NAME} ${SOURCE})

target_include_directories(${PROJECT_NAME} PUBLIC ../graph_lib/)




