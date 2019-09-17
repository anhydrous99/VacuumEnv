cmake_minimum_required(VERSION 3.14)
project(CSCI6350_project1)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE BOOL "Build nlohmann's json tests" FORCE)
add_subdirectory(extern/json)

add_executable(CSCI6350_project1
        custom_assertion.h
        main.cpp
        Environment.h
        Environment.cpp
        cell.h
        cell.cpp
        vacuum.h
        vacuum.cpp parser.cpp parser.h)

target_link_libraries(CSCI6350_project1 nlohmann_json::nlohmann_json)

configure_file(${CMAKE_SOURCE_DIR}/conf.json ${CMAKE_BINARY_DIR}/conf.json COPYONLY)
