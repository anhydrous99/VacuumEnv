cmake_minimum_required(VERSION 3.14)
project(VacuumEnv)

set(CMAKE_CXX_STANDARD 14)

set(JSON_BuildTests OFF CACHE BOOL "Build nlohmann's json tests" FORCE)
add_subdirectory(extern/json)

add_executable(VacuumEnv
        custom_assertion.h
        main.cpp
        Environment.h
        Environment.cpp
        cell.h
        cell.cpp
        vacuum.h
        vacuum.cpp
        parser.cpp
        parser.h
        )

target_link_libraries(VacuumEnv nlohmann_json::nlohmann_json)

configure_file(${CMAKE_SOURCE_DIR}/conf.json ${CMAKE_BINARY_DIR}/conf.json COPYONLY)
