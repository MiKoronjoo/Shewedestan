cmake_minimum_required(VERSION 3.14)
project(Shewedestan)

set(CMAKE_CXX_STANDARD 17)


add_executable(
        Shewedestan
        shewedpolo/City.cpp
        shewedpolo/Path.cpp
        shewedpolo/Node.cpp
        shewedpolo/Edge.cpp
        shewedpolo/KDTree.cpp
        main.cpp
)
