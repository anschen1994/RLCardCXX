cmake_minimum_required(VERSION 3.15)

project(rlcard)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(COMMON_FLAGS "")

# header
include_directories(${PROJECT_SOURCE_DIR}/config)
include_directories(${PROJECT_SOURCE_DIR}/game_engine)
include_directories((${PROJECT_SOURCE_DIR}/utils))

# source file
file(GLOB_RECURSE RLCARD_SRC_FILE ${PROJECT_SOURCE_DIR}/game_engine/*.cpp)
list(APPEND RLCARD_SRC_FILE ${PROJECT_SOURCE_DIR}/utils/helper.cpp)

add_library(rlcard SHARED ${RLCARD_SRC_FILE})