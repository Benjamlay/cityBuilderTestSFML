cmake_minimum_required(VERSION 3.31)

option(ENABLE_TESTING "Enable gtest" OFF)
if(ENABLE_TESTING)
    list(APPEND VCPKG_MANIFEST_FEATURES "testing")
endif(ENABLE_TESTING)

project(cityBuilder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ENABLE_TESTING)
    enable_testing()
    find_package(GTest CONFIG REQUIRED)
endif(ENABLE_TESTING)

#packages : external libraries managed by


add_subdirectory(core/)
add_subdirectory(game/)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(cityBuilder main.cc)

target_link_libraries(cityBuilder PRIVATE game)

