﻿find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cc)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_library(game ${SRC_FILES} ${HEADER_FILES})

target_include_directories(game PUBLIC include/)
target_link_libraries(game PUBLIC core SFML::System SFML::Graphics SFML::Window)

