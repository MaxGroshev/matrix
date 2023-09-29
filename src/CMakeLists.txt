cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(triangles)

#-----------------------------------------------------------------------------------------

#Root dir src
set(SOURCE
    ./main.cpp)

#Figures
set(FIGURES_SRC)

#Debug
set(DEBUG_UTILS
    ../debug_utils/error_control.cpp)

include_directories(${PROJECT_NAME} PRIVATE ./figures/include)

#-----------------------------------------------------------------------------------------

add_library(figures ${FIGURES_SRC})

add_executable(${PROJECT_NAME} ${SOURCE} ${DEBUG_UTILS})
target_link_libraries(${PROJECT_NAME} figures)





