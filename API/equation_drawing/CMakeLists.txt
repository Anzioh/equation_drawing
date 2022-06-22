cmake_minimum_required(VERSION 3.20)
project(equation_drawing)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(nlohmann)

add_executable(equation_drawing
        nlohmann/json.hpp
        Caculater.cpp
        Caculater.h
        Equation.cpp
        Equation.h
        main.cpp
        Viewer.cpp
        Viewer.h
		Variable.cpp
		Variable.h
		atmsp.h)
