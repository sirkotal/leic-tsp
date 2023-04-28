cmake_minimum_required(VERSION 3.23)
project(leic_tsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(leic_tsp src/main.cpp src/graph.cpp src/graph.h)
