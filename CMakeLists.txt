cmake_minimum_required(VERSION 3.31)
project(core)

set(CMAKE_CXX_STANDARD 20)
set(GOOGLE_TEST OFF)
if (GOOGLE_TEST)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.17.0
    )
    FetchContent_MakeAvailable(googletest)
endif ()

add_library(core STATIC cust_bash64.cpp
        platform_export.h)

