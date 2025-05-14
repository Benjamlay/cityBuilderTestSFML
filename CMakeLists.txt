cmake_minimum_required(VERSION 3.31)
project(cityBuilder)

set(CMAKE_CXX_STANDARD 20)

#packages : external libraries managed by
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(core/)

file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

add_executable(cityBuilder main.cc)

target_link_libraries(cityBuilder PRIVATE core SFML::Graphics SFML::Window SFML::System)
