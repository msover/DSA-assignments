cmake_minimum_required(VERSION 4.1)
project(DSA_assignments)

set(CMAKE_CXX_STANDARD 14)

include_directories()

add_executable(DSA_assignments
		App.cpp
		tests/ExtendedTest.cpp
		tests/ExtendedTest.h
		Set.cpp
		Set.h
		SetIterator.cpp
		SetIterator.h
		tests/ShortTest.cpp
		tests/ShortTest.h
		App.cpp
		App.cpp)
