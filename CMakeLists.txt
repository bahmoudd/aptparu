cmake_minimum_required(VERSION 3.16)

project(aptparu)

# fetch latest argparse
include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
)
FetchContent_MakeAvailable(argparse)

# fetch latest fmt
include(FetchContent)
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt
    GIT_TAG 407c905e45ad75fc29bf0f9bb7c5c2fd3475976f
)
FetchContent_MakeAvailable(fmt)

file(GLOB SOURCES "src/*.cpp")

add_executable(aptparu ${SOURCES})
target_link_libraries(aptparu argparse)
target_link_libraries(aptparu fmt)