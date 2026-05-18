cmake_minimum_required(VERSION 4.1)
project(SortedMultiMapHash)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(SortedMultiMapHash
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SMMIterator.cpp
        SMMIterator.h
        SortedMultiMap.cpp
        SortedMultiMap.h)
