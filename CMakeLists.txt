cmake_minimum_required(VERSION 3.6)
project(interview)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# for cmake debug
set(CMAKE_BUILD_TYPE Debug)
# set(CMAKE_C_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

add_subdirectory(code/algo/getoffer/c++/1)
add_subdirectory(code/linuxsystem/stat)
add_subdirectory(code/standalone/c++)
