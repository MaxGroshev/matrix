cmake_minimum_required(VERSION 3.21)

#-----------------------------------------------------------------------------------------

project(matrix)

#-----------------------------------------------------------------------------------------

# set(TESTING_ENABLED ON CACHE BOOL [FORCE])
# set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#-----------------------------------------------------------------------------------------

set(CMAKE_BUILD_TYPE "Debug")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS  -fsanitize=address,leak)
    add_compile_definitions(MY_DEBUG)
endif ()

#-----------------------------------------------------------------------------------------

add_subdirectory(debug_utils/)
add_subdirectory(matrix/)

# if (TESTING_ENABLED)
    # add_subdirectory(./tests/)
# endif()

unset(TESTING_ENABLED CACHE)

