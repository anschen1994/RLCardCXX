cmake_minimum_required(VERSION 3.15)

project(rlcard)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# flags
set(COMMON_FLAGS "")
if("${CMAKE_BUILD_TYPE}" MATCHES "Debug")
    set(COMMON_FLAGS "${COMMON_FLAGS} -Wall -g")
elseif("${CMAKE_BUILD_TYPE}" MATCHES "Release")
    set(COMMON_FLAGS "${COMMON_FLAGS} -Wall")
endif()

message(STATUS "FLAGS:${COMMON_FLAGS}")
# header
include_directories(${PROJECT_SOURCE_DIR}/config)
include_directories(${PROJECT_SOURCE_DIR}/game_engine)
include_directories((${PROJECT_SOURCE_DIR}/utils))
include_directories(${PROJECT_SOURCE_DIR})

# source file
file(GLOB_RECURSE RLCARD_SRC_FILE ${PROJECT_SOURCE_DIR}/game_engine/black_jack/*.cpp)
list(APPEND RLCARD_SRC_FILE ${PROJECT_SOURCE_DIR}/game_engine/base_engine.cpp)
# list(APPEND RLCARD_SRC_FILE ${PROJECT_SOURCE_DIR}/utils/helper.cpp)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
add_library(rlcard SHARED ${RLCARD_SRC_FILE})

