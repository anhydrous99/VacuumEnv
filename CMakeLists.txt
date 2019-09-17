cmake_minimum_required(VERSION 3.14)
project(CSCI6350_project1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(extern/cxxopts)
add_subdirectory(extern/json)

add_executable(CSCI6350_project1
        custom_assertion.h
        main.cpp
        Environment.h
        Environment.cpp
        cell.h
        cell.cpp
        vacuum.h
        vacuum.cpp)

target_link_libraries(CSCI6350_project1 cxxopts nlohmann_json::nlohmann_json)
