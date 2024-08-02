cmake_minimum_required(VERSION 3.28)
project(Algorytmy_sortowania)

set(CMAKE_CXX_STANDARD 26)

add_executable(Algorytmy_sortowania main.cpp
        introSort.h
        mergeSort.h
        quickSort.h)
