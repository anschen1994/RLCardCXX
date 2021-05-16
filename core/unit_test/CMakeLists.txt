cmake_minimum_required(VERSION 3.15)
project(unit_test)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "-Wall -g")

get_filename_component(PARENT_DIRECTORY ${PROJECT_SOURCE_DIR} DIRECTORY)

include_directories(${PARENT_DIRECTORY}/game_engine)
include_directories(${PARENT_DIRECTORY}/utils)
include_directories(${PARENT_DIRECTORY}/config)
include_directories(${PARENT_DIRECTORY}/spdlog)
include_directories(${PARENT_DIRECTORY})

link_directories(${PARENT_DIRECTORY}/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
add_executable(unit_test ${PROJECT_SOURCE_DIR}/test_blackjack.cpp)
target_link_libraries(unit_test -lrlcard)
target_link_libraries(unit_test -lspdlog)