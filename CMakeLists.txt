cmake_minimum_required(VERSION 3.31)

option(ENABLE_TESTING "Enable gtest" OFF)
if(ENABLE_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif(ENABLE_TESTING)

option(ENABLE_PROFILING "Enable tracy" OFF)
if(ENABLE_PROFILING)
    list(APPEND VCPKG_MANIFEST_FEATURES "profiling")
endif(ENABLE_PROFILING)

project(cityBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_TESTING)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif(ENABLE_TESTING)

#packages : external libraries managed by

if(ENABLE_PROFILING)
    find_package(Tracy CONFIG REQUIRED)
endif(ENABLE_PROFILING)


add_subdirectory(core/)
add_subdirectory(game/)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(cityBuilder main.cc)

target_link_libraries(cityBuilder PRIVATE game)

