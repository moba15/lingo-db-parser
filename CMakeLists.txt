cmake_minimum_required(VERSION 3.30)
project(lingo_db_parser)

set(CMAKE_CXX_STANDARD 26)
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
include_directories(lingo_db_parser PRIVATE include)
include_directories(lingo_db_parser cmake-build-debug-system/src)
add_subdirectory(src)