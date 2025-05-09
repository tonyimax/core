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

#add_library(core STATIC cust_bash64.cpp
#        platform_export.h)
add_library(core SHARED cust_bash64.cpp
        platform_export.h
        cust_md5.cpp
        cust_md5.h)

#-fPIC
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)
