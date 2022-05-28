cmake_minimum_required(VERSION 3.19)
project(zeta)

set(CMAKE_CXX_STANDARD 17)

add_executable(zeta main.cpp)

find_package(OpenCV REQUIRED)
target_link_libraries(zeta ${OpenCV_LIBS})